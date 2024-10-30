#define MAX_INPUT_SIZE 256

#include "config.h"

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

Item items[] = {
        {"KEY", "a KEY", 1, {56, "AXE", "You opened a tool shed and took an axe", false}},
        {"AXE",           "an AXE",             1, {67, "STICKS",        "You cut sticks for sheeplegs",                                        false}},
        {"STICKS",        "STICKS",             1, {43, "sheeplegs",     "You prepared legs for your fake sheep",                               true}},
        {"sheeplegs",     "sheeplegs",          0},
        {"MUSHROOMS",     "MUSHROOMS",          1, {34, "MONEY",         "The tavern owner paid you money",                                     false}},
        {"MONEY",         "MONEY",              1, {37, "BARREL",        "The cooper sold you a new barrel",                                    false}},
        {"BARREL",        "a BARREL",           1, {43, "sheeptrunk",    "You made a nice sheeptrunk",                                          true}},
        {"sheeptrunk",    "a sheeptrunk",       0},
        {"BERRIES",       "BERRIES",            1, {36, "WOOL",          "The butcher gave you wool",                                           false}},
        {"WOOL",          "WOOL",               1, {43, "sheepskin",     "You prepared skin for your fake sheep",                               true}},
        {"sheepskin",     "a sheepskin"},
        {"BAG",           "a BAG",              1, {57, "RAG",           "You used your tools to make a rag",                                   false}},
        {"RAG",           "a RAG",              1, {43, "sheephead",     "You made a fake sheephead",                                           true}},
        {"sheephead",     "sheeohead",          0},
        {"SPADE",         "a SPADE",            1, {11, "SULPHUR",       "You are digging... and digging...  That's enough sulphur for you",    false}},
        {"SULPHUR",       "a SULPHUR",          1, {43, "solid poison",  "You prepared a solid poison",                                         true}},
        {"solid poison",  "a solid poison"},
        {"BUCKET",        "a BUCKET",           1, {21, "TAR",           "You got a bucket full of tar",                                        false}},
        {"TAR",           "TAR",                1, {43, "liquid poison", "You prepared a liquid poison",                                        true}},
        {"liquid poison", "a liquid poison"},
        {"dead dragon",   "a dead dragon"},
        {"STONE", "a STONE", 1},
        {"FISH",          "a FISH",             1},
        {"KNIFE",         "a KNIFE",            1, {43, "DRAGONSKIN",    "You cut a piece of dragon's skin",                                    false}},
        {"DRAGONSKIN",    "a DRAGONSKIN",       1, {57, "SHOES",         "You used your tools to make shoes",                                   false}},
        {"SHOES",         "a dragonskin SHOES", 1, {41, "PRIZE",         "The King is impressed by your shoes",                                 false}},
        {"PRIZE",         "a PRIZE",            1},
        {"SHEEP",         "a SHEEP",            1, {43, "dead dragon",   "The dragon noticed your gift... The dragon ate your sheep and died!", false}}
};

const int ITEMS_LENGTH = sizeof(items) / sizeof(Item);

Location locations[] = {
        {"You are inside a brimstone mine", 11, {EAST}},
        {"You are at the entrance to the mine",   12, {EAST,  WEST}},
        {"A hill", 13, {EAST, WEST, SOUTH}, "STONE"},
        {"Some bushes",                           14, {EAST,  WEST}},
        {"An old deserted hut",                   15, {EAST,  WEST},                "BUCKET"},
        {"The edge of a forest",                  16, {EAST,  WEST}},
        {"A dark forest",                         17, {WEST,  SOUTH},               "MUSHROOMS"},
        {"A man nearby making tar",               21, {EAST,  SOUTH}},
        {"A timber yard",                         22, {WEST,  EAST,  SOUTH}},
        {"You are by a roadside shrine",          23, {WEST,  EAST,  SOUTH, NORTH}, "KEY"},
        {"You are by a small chapel",             24, {WEST,  EAST}},
        {"You are on a road leading to a wood",   25, {WEST,  EAST,  SOUTH}},
        {"You are in a forest",                   26, {WEST,  EAST}},
        {"You are in a deep forest",              27, {WEST,  NORTH},               "BERRIES"},
        {"You are by the Vistula River",          31, {EAST,  NORTH}},
        {"You are by the Vistula River",          32, {WEST,  NORTH},               "FISH"},
        {"You are on a bridge over river",        33, {SOUTH, NORTH}},
        {"You are by the old tavern",             34, {EAST}},
        {"You are at the town's end",             35, {WEST,  NORTH, SOUTH}},
        {"You are in a butcher's shop",           36, {SOUTH}},
        {"You are in a cooper's house",           37, {SOUTH}},
        {"You are in the Wawel Castle",           41, {EAST}},
        {"You are inside a dragon's cave",        42, {EAST,  WEST}},
        {"A perfect place to set a trap",         43, {NORTH, WEST}},
        {"You are by the water mill",             44, {EAST},                       "BAG"},
        {"You are at a main crossroad",           45, {EAST,  WEST,  SOUTH, NORTH}},
        {"You are on a town street",              46, {EAST,  WEST,  NORTH}},
        {"You are in a frontyard of your house",  47, {WEST,  NORTH, SOUTH}},
        {"You are by a swift stream",             54, {EAST}},
        {"You are on a street leading forest",    55, {WEST,  SOUTH, NORTH},        "KNIFE"},
        {"You are in a woodcutter's backyard",    56, {SOUTH}},
        {"You are in a shoemaker's house",        57, {NORTH}},
        {"You are in a bleak funeral house",      64, {EAST},                       "SPADE"},
        {"You are on a path leading to the wood", 65, {EAST,  WEST,  NORTH}},
        {"You are at the edge of a forest",       66, {EAST,  WEST,  NORTH}},
        {"You are in a deep forest",              67, {WEST}}
};

const int LOCATIONS_LENGTH = sizeof(locations) / sizeof(Location);
