#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <synchapi.h>
#include "src/include/config.h"
#include "src/include/help.h"
#include "prompt.h"

void show_location(Location* location, Item* carryingItem) {
//    clear();
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

void go(Location **location, enum Directions direction) {
    if (!can_go(**location, direction)) {
        return;
    }
    int new_position = (**location).position + get_diff(direction);
    clear();
    printf("You are going %s...\n", locale_direction(direction));
    Sleep(1000);
    clear();
    *location = &*get_location(new_position);
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
    return 0;
}

bool is_carrying_item(Item *carrying_item) {
    return carrying_item != NULL;
}

void handle_movement(Location **location, char action) {
    int direction;
    switch (action) {
        case 'W': direction = WEST; break;
        case 'E': direction = EAST; break;
        case 'S': direction = SOUTH; break;
        case 'N': direction = NORTH; break;
        default: return;
    }

    if (!can_go(**location, direction)) {
        cant_go();
    } else {
        go(location, direction);
    }
}

void handle_drop(Location *location, Item **carrying_item, const char *arg) {
    if (!is_carrying_item(*carrying_item)) {
        clear();
        printf("You are not carrying anything\n");
        Sleep(1000);
        return;
    }

    if (strcmp(arg, (*carrying_item)->name) != 0) {
        clear();
        printf("You haven't got an item like that\n");
        Sleep(1000);
        return;
    }

    bool space_found = false;
    for (int i = 0; i < MAX_ITEMS_PER_LOCATION; i++) {
        if (location->items[i] == NULL) {
            location->items[i] = *carrying_item;
            *carrying_item = NULL;
            space_found = true;

            clear();
            printf("You are dropping %s\n", location->items[i]->label);
            Sleep(1000);
            break;
        }
    }

    if (!space_found) {
        clear();
        printf("There is not enough space in this location\n");
        Sleep(1000);
    }
}

void handle_take(Location *location, Item **carrying_item, const char *arg) {
    if (is_carrying_item(*carrying_item)) {
        clear();
        printf("You are already carrying something\n");
        Sleep(1000);
        return;
    }

    bool item_found = false;
    for (int i = 0; i < MAX_ITEMS_PER_LOCATION; i++) {
        Item **item = &location->items[i];
        if (*item == NULL || strcmp((*item)->name, arg) != 0) continue;

        if ((*item)->flag == 0) {
            clear();
            printf("You can't carry that\n");
            Sleep(1000);
            return;
        }

        *carrying_item = get_item(arg);
        *item = NULL;
        item_found = true;

        clear();
        printf("You are taking %s\n", (*carrying_item)->label);
        Sleep(1000);
        break;
    }

    if (!item_found) {
        clear();
        printf("There isn't anything like that here\n");
        Sleep(1000);
    }
}



void handle_use(Location *location, Item **carrying_item, const char *arg, int *milestones) {
    Item *item = *carrying_item;
    if (strcmp(arg, item->name) != 0) {
        clear();
        printf("You dont have item like that\n");
        Sleep(1000);
        return;
    }

    if (item->useAction.location != location->position) {
        clear();
        printf("Nothing happened\n");
        Sleep(1000);
        return;
    }

    clear();
    printf("You are using %s\n", item->label);
    Sleep(1000);

    UseAction action = item->useAction;
    if (action.milestone == true) {
        (*milestones)++;
    }

    Item *new_item = get_item(action.newItem);
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

    clear();
    printf("%s\n", action.message);
    Sleep(1000);
}

int main(void) {
    init_start_items();

    Location *location = get_location(START_POSITION);
    Item* carrying_item = NULL;
    int milestones = 0;

    while (1) {
        char command[MAX_INPUT_SIZE];
        char arg[MAX_INPUT_SIZE];
        if (milestones == 6) {
            //@TODO GIVE SHEEP AND BREAK ON USE PRIZE
            break;
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
                handle_movement(&location, action);
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
                handle_use(location, &carrying_item, arg, &milestones);
                break;
            default:
                printf("Try another word or V for vocabulary\n");
                Sleep(2000);
        }
    }

    return 0;
}
