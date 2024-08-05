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
    for (int i = 0; i < 6; i++) {
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
    printf("You are going %s...", locale_direction(direction));
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
            locations[i].items[0] = item;
        }
    }
}

char get_command_action(char* command) {
    printf("%s, %s, %d, %d\n", command, "EAST", strcmp(command, "EAST"), strcmp(command, "E"));
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

int main(void) {
    init_start_items();

    Location *location = get_location(START_POSITION);
    Item* carrying_item = NULL;
    char command[MAX_INPUT_SIZE];
    char arg[MAX_INPUT_SIZE];
    int milestones = 0;

    while (1) {
        if (milestones == 6) {
            //@TODO GIVE SHEEP AND BREAK ON USE PRIZE
            break;
        }
        strcpy((char *) &command, "");
        strcpy((char *) &arg, "");
        show_location(location, carrying_item);

        listen_for_command((char *) &command, (char *) &arg);

        char action = get_command_action(command);
        if (action == 'W') {
            if (!can_go(*location, WEST)) {
                cant_go();
                continue;
            }
            go(&location, WEST);
        } else if (action == 'E') {
            if (!can_go(*location, EAST)) {
                cant_go();
                continue;
            }
            go(&location, EAST);
        } else if (action == 'S') {
            if (!can_go(*location, SOUTH)) {
                cant_go();
                continue;
            }
            go(&location, SOUTH);
        } else if (action == 'N') {
            if (!can_go(*location, NORTH)) {
                cant_go();
                continue;
            }
            go(&location, NORTH);
        } else if (action == 'G') {
            gossip();
            continue;
        } else if (action == 'V') {
            vocabulary();
            continue;
        } else if (action == 'D') {
            // DROP
            continue;
        } else if (action == 'T') {
            // TAKE
            continue;
        } else if (action == 'U') {
            // USE
            continue;
        } else {
            printf("Try another word or V for vocabulary\n");
            Sleep(2000);
            continue;
        }
    }

    return 0;
}
