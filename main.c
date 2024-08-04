#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <synchapi.h>
#include "config/config.h"
#include "help/help.h"

void show_location(Location location) {
    clear();
    char can_go[100] = "You can go ";
    int can_go_added = 0;
    for (int i = 0; i < 4; i++) {
        enum Directions direction = location.directions[i];
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

    char see[100] = "You can see ";

    printf("%s %d\n"
           "%s\n"
           "%s\n", location.description, location.position, can_go, see);
}

Location get_location(int position) {
    for (int i = 0; i < LOCATIONS_LENGTH; i++) {
        if (locations[i].position == position) {
            return locations[i];
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

void go(Location *location, enum Directions direction) {
    if (!can_go(*location, direction)) {
        cant_go();
        return;
    }
    int new_position = location->position + get_diff(direction);
    clear();
    printf("You are going %s...", locale_direction(direction));
    Sleep(1000);
    clear();
    Location new_location = get_location(new_position);
    *location = new_location;
}

int main(void) {
    Location location = get_location(START_POSITION);
    show_location(location);
    Sleep(3000);

    go(&location, EAST);
    show_location(location);
    Sleep(3000);

    go(&location, EAST);
    show_location(location);

    return 0;
}
