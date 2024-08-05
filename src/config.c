#include "config.h"
#include "include/config.h"

char* locale_direction(enum Directions direction) {
    switch (direction) {
        case WEST:
            return "WEST";
        case NORTH:
            return "NORTH";
        case EAST:
            return "EAST";
        case SOUTH:
            return "SOUTH";
    }
}

int get_diff(enum Directions direction) {
    switch (direction) {
        case NORTH:
            return -10;
        case EAST:
            return 1;
        case SOUTH:
            return 10;
        case WEST:
            return -1;
    }
}

Location locations[] = {
        {"You are inside a brimstone mine", 11, {EAST}},
        {"You are at the entrance to the mine", 12, {EAST, WEST}},
        {"A hill", 13, {EAST, WEST, SOUTH}, "STONE"},
};

const int LOCATIONS_LENGTH = sizeof(locations) / sizeof(Location);

const Item items[] = {
        {"KEY", "a KEY", 1, {56, "AXE", "You opened a tool shed and took an axe", false}},
        {"sheeplegs", "sheeplges", 0},
};

const int ITEMS_LENGTH = sizeof(items) / sizeof(Item);