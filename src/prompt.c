#include "prompt.h"
#include <stdio.h>
#include <string.h>

static void split_input(const char *input, char *command, char *arg) {
    char *space_ptr = strchr(input, ' ');

    if (space_ptr != NULL) {
        size_t command_length = space_ptr - input;
        strncpy(command, input, command_length);
        command[command_length] = '\0';

        strncpy(arg, space_ptr + 1, MAX_INPUT_SIZE - command_length - 1);
        arg[strcspn(arg, "\n")] = '\0';
    } else {
        strncpy(command, input, MAX_INPUT_SIZE - 1);
        command[strcspn(command, "\n")] = '\0';
        arg[0] = '\0';
    }
}

void listen_for_command(char *commandPtr, char *argPtr) {
    char input[MAX_INPUT_SIZE];

    if (fgets(input, sizeof(input), stdin) != NULL) {
        split_input(input, commandPtr, argPtr);
    }
}