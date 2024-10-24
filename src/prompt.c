#include "include/prompt.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void listen_for_command(char *commandPtr, char *argPtr) {
    char input[MAX_INPUT_SIZE];
    if(fgets (input, MAX_INPUT_SIZE, stdin) != NULL) {
        char command[MAX_INPUT_SIZE] = "";
        char arg[MAX_INPUT_SIZE] = "";
        bool was_space = false;
        int command_length = 0;
        for (int i=0; input[i] != '\0' && input[i] != '\n'; i++) {
            if (input[i] == ' ') {
                command_length = i + 1;
                was_space = true;
                continue;
            };
            if (was_space) {
                arg[i - command_length] = input[i];
                arg[(i - command_length) + 1] = '\0';
            } else {
                command[i] = input[i];
                command[i + 1] = '\0';
            }
        }
        strcpy(commandPtr, command);
        strcpy(argPtr, arg);
    }
}