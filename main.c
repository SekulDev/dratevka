#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <synchapi.h>

#ifdef _WIN32

#include <windows.h>

#define SLEEP_MS(ms) Sleep(ms)
#else
#include <unistd.h>
#define SLEEP_MS(ms) usleep((ms) * 1000)
#endif
#include "include/config.h"
#include "include/help.h"
#include "include/prompt.h"

void display_message(const char *format, ...) {
    va_list args;
    va_start(args, format);
    clear();
#ifdef _IS_DEBUG
    fflush(stdout);
#endif
    vprintf(format, args);
    SLEEP_MS(1000);
    va_end(args);
}

void show_location(Location* location, Item* carryingItem) {
    char can_go[100] = "You can go ";
    int can_go_added = 0;
    for (int i = 0; i < 4; i++) {
        enum Directions direction = location->directions[i];
        if (direction != 0) {
            if (can_go_added != 0) {
                strcat(can_go, ", ");
            }
            can_go_added++;
            strcat(can_go, locale_direction(direction));
        }
    }
    if (can_go_added == 0) {
        strcat(can_go, "NOWHERE");
    }

    char see[150] = "You can see ";
    int see_added = 0;
    for (int i = 0; i < MAX_ITEMS_PER_LOCATION; i++) {
        Item* item = location->items[i];
        if (item == NULL) continue;
        if (see_added != 0) {
            strcat(see, ", ");
        }
        see_added++;
        strcat(see, item->label);
    }
    if (see_added == 0) {
        strcat(see, "NOTHING");
    }

    char carrying[50] = "You carrying ";
    if (carryingItem == NULL) {
        strcat(carrying, "NOTHING");
    } else {
        strcat(carrying, carryingItem->label);
    }

#ifdef _IS_DEBUG
    fflush(stdout);
#endif
    printf("%s %d\n"
           "%s\n"
           "%s\n"
           "%s\n", location->description, location->position, can_go, see, carrying);
}

Location* get_location(int position) {
    for (int i = 0; i < LOCATIONS_LENGTH; i++) {
        if (locations[i].position == position) {
            return &locations[i];
        }
    }
    return NULL;
}

bool can_go(Location location, enum Directions direction) {
     for (int i = 0; i < 4; i++) {
         if (location.directions[i] == direction) {
             return true;
         }
     }
     return false;
}

void go(Location **location, enum Directions direction, const bool *isDragonDead) {
    if (!can_go(**location, direction)) {
        return;
    }
    int new_position = (**location).position + get_diff(direction);
    Location *new_location = &*get_location(new_position);
    if (new_location->position == 42 && !(*isDragonDead)) {
        display_message("You can't go that way...  The dragon sleeps in a cave!\n");
        return;
    }
    display_message("You are going %s...\n", locale_direction(direction));
    clear();
    *location = new_location;
}

Item* get_item(const char* name) {
    for (int i=0; i<ITEMS_LENGTH; i++) {
        if (strcmp(items[i].name, name) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

void init_start_items() {
    for (int i=0; i<LOCATIONS_LENGTH; i++) {
        if (locations[i].startItem[0] != '\0') {
            Item* item = get_item(locations[i].startItem);
            if (item == NULL) continue;
            locations[i].items[0] = &*item;
        }
    }
}

char get_command_action(char* command) {
    if (strcmp(command, "WEST") == 0 || strcmp(command, "W") == 0) return 'W';
    if (strcmp(command, "EAST") == 0 || strcmp(command, "E") == 0) return 'E';
    if (strcmp(command, "SOUTH") == 0 || strcmp(command, "S") == 0) return 'S';
    if (strcmp(command, "NORTH") == 0 || strcmp(command, "N") == 0) return 'N';
    if (strcmp(command, "VOCABULARY") == 0 || strcmp(command, "V") == 0) return 'V';
    if (strcmp(command, "GOSSIPS") == 0 || strcmp(command, "G") == 0) return 'G';
    if (strcmp(command, "TAKE") == 0 || strcmp(command, "T") == 0) return 'T';
    if (strcmp(command, "DROP") == 0 || strcmp(command, "D") == 0) return 'D';
    if (strcmp(command, "USE") == 0 || strcmp(command, "U") == 0) return 'U';
    return '\0';
}

bool is_carrying_item(Item *carrying_item) {
    return carrying_item != NULL;
}

void handle_movement(Location **location, char action, bool *isDragonDead) {
    int direction;
    switch (action) {
        case 'W': direction = WEST; break;
        case 'E': direction = EAST; break;
        case 'S': direction = SOUTH; break;
        case 'N': direction = NORTH; break;
        default: return;
    }

    if (!can_go(**location, direction)) {
        display_message("You cant go that way\n");
        clear();
    } else {
        go(location, direction, isDragonDead);
    }
}

void handle_drop(Location *location, Item **carrying_item, const char *arg) {
    if (!is_carrying_item(*carrying_item)) {
        display_message("You are not carrying anything\n");
        return;
    }

    if (strcmp(arg, (*carrying_item)->name) != 0) {
        display_message("You haven't got an item like that\n");
        return;
    }

    bool space_found = false;
    for (int i = 0; i < MAX_ITEMS_PER_LOCATION; i++) {
        if (location->items[i] == NULL) {
            location->items[i] = *carrying_item;
            *carrying_item = NULL;
            space_found = true;

            display_message("You are dropping %s\n", location->items[i]->label);
            break;
        }
    }

    if (!space_found) {
        display_message("There is not enough space in this location\n");
    }
}

void handle_take(Location *location, Item **carrying_item, const char *arg) {
    if (is_carrying_item(*carrying_item)) {
        display_message("You are already carrying something\n");
        return;
    }

    bool item_found = false;
    for (int i = 0; i < MAX_ITEMS_PER_LOCATION; i++) {
        Item **item = &location->items[i];
        if (*item == NULL || strcmp((*item)->name, arg) != 0) continue;

        if ((*item)->flag == 0) {
            display_message("You can't carry that\n");
            return;
        }

        *carrying_item = get_item(arg);
        *item = NULL;
        item_found = true;

        display_message("You are taking %s\n", (*carrying_item)->label);
        break;
    }

    if (!item_found) {
        display_message("There isn't anything like that here\n");
    }
}


void handle_use(Location *location, Item **carrying_item, const char *arg, int *milestones, bool *isDragonDead) {
    Item *item = *carrying_item;
    if (strcmp(arg, item->name) != 0) {
        display_message("You dont have item like that\n");
        return;
    }

    if (item->useAction.location != location->position) {
        display_message("Nothing happened\n");
        return;
    }

    if (strcmp(item->name, "KNIFE") == 0 && !(*isDragonDead)) {
        display_message("Nothing happened\n");
        return;
    }

    display_message("You are using %s\n", item->label);

    UseAction action = item->useAction;
    if (action.milestone == true) {
        (*milestones)++;
        if (*milestones == 6) {
            *carrying_item = get_item("SHEEP");
        }
    }

    Item *new_item = get_item(action.newItem);

    if (strcmp(new_item->name, "dead dragon") == 0) {
        (*isDragonDead) = true;
        for (int i = 0; i < MAX_ITEMS_PER_LOCATION; i++) {
            location->items[i] = NULL;
        }
    }

    if (new_item->flag == 1) {
        *carrying_item = new_item;
    } else {
        for (int i = 0; i < MAX_ITEMS_PER_LOCATION; i++) {
            if (location->items[i] == NULL) {
                location->items[i] = &*new_item;
                *carrying_item = NULL;

                break;
            }
        }
    }

    display_message("%s\n", action.message);
}

int main(void) {
    init_start_items();

    Location *location = get_location(START_POSITION);
    Item* carrying_item = NULL;
    int milestones = 0;
    bool isDragonDead = false;

    while (1) {
        char command[MAX_INPUT_SIZE];
        char arg[MAX_INPUT_SIZE];
        if (milestones == 6) {
            if (strcmp(carrying_item->name, "PRIZE") == 0) {
                display_message("You finished the game. Congratulations!\n");
                break;
            }
        }
        strcpy((char *) &command, "");
        strcpy((char *) &arg, "");

        show_location(location, carrying_item);
        listen_for_command((char *) &command, (char *) &arg);

        char action = get_command_action(command);

        switch (action) {
            case 'W':
            case 'E':
            case 'S':
            case 'N':
                handle_movement(&location, action, &isDragonDead);
                break;
            case 'G':
                gossip();
                break;
            case 'V':
                vocabulary();
                break;
            case 'D':
                handle_drop(location, &carrying_item, arg);
                break;
            case 'T':
                handle_take(location, &carrying_item, arg);
                break;
            case 'U':
                handle_use(location, &carrying_item, arg, &milestones, &isDragonDead);
                break;
            default:
                display_message("Try another word or V for vocabulary\n");
                SLEEP_MS(1000);
                break;
        }
    }

    return 0;
}
