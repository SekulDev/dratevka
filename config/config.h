#ifndef DRATEVKA_CONFIG_H
#define DRATEVKA_CONFIG_H

#define ITEM_NAME_SIZE 30
//#define START_POSITION 47
#define START_POSITION 11 // temporary only

#include <stdbool.h>

enum Directions {
    NORTH = 1,
    EAST,
    SOUTH,
    WEST
};

char* locale_direction(enum Directions direction);

int get_diff(enum Directions);

typedef struct {
    char description[100];
    int position;
    enum Directions directions[4];
    char startItem[ITEM_NAME_SIZE];
} Location;

extern Location locations[];

extern const int LOCATIONS_LENGTH;

typedef struct {
    int location;
    char newItem[ITEM_NAME_SIZE];
    char message[500];
    bool milestone;
} UseAction;

typedef struct {
    char name[ITEM_NAME_SIZE];
    char label[ITEM_NAME_SIZE];
    bool flag;
    UseAction useAction;
} Item;

extern const Item items[];

extern const int ITEMS_LENGTH;

#endif //DRATEVKA_CONFIG_H
