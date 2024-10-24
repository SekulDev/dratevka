#include "include/help.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <stdlib.h>
#endif

void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void gossip() {
    clear();
    printf("The  woodcutter lost  his home key...\n"
           "The butcher likes fruit... The cooper\n"
           "is greedy... Dratewka plans to make a\n"
           "poisoned  bait for the dragon...  The\n"
           "tavern owner is buying food  from the\n"
           "pickers... Making a rag from a bag...\n");
    system("pause");
    clear();
}

void vocabulary() {
    clear();
    printf("NORTH or N, SOUTH or S\n"
           "WEST or W, EAST or E\n"
           "TAKE (object) or T (object)\n"
           "DROP (object) or D (object)\n"
           "USE (object) or U (object)\n"
           "GOSSIPS or G, VOCABULARY or V\n");
    system("pause");
    clear();
}

void cant_go() {
    clear();
    printf("You can't go that way\n");
    Sleep(1000);
    clear();
}