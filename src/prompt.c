#include "prompt.h"
#include <stdio.h>
#include <string.h>

void split_input(const char* input, char* command, char* arg) {
    if (input == NULL || command == NULL || arg == NULL) {
        if (command) command[0] = '\0';
        if (arg) arg[0] = '\0';
        return;
    }

    // clear output buffers
    command[0] = '\0';
    arg[0] = '\0';

    // clean input buffer
    char cleaned_input[MAX_INPUT_SIZE];
    strncpy(cleaned_input, input, MAX_INPUT_SIZE - 1);
    cleaned_input[MAX_INPUT_SIZE - 1] = '\0';  // ensure null termination

    // remove newline if present
    char* newline = strchr(cleaned_input, '\n');
    if (newline) {
        *newline = '\0';
    }

    char* space_ptr = strchr(cleaned_input, ' ');
    if (space_ptr != NULL) {
        size_t cmd_length = space_ptr - cleaned_input;
        if (cmd_length >= MAX_INPUT_SIZE) {
            cmd_length = MAX_INPUT_SIZE - 1;
        }
        strncpy(command, cleaned_input, cmd_length);
        command[cmd_length] = '\0';
        
        strncpy(arg, space_ptr + 1, MAX_INPUT_SIZE - 1);
        arg[MAX_INPUT_SIZE - 1] = '\0';
    } else {
        strncpy(command, cleaned_input, MAX_INPUT_SIZE - 1);
        command[MAX_INPUT_SIZE - 1] = '\0';
    }
}

void listen_for_command(char* command, char* arg) {
    char input[MAX_INPUT_SIZE];
    command[0] = '\0';
    arg[0] = '\0';

    if (fgets(input, sizeof(input), stdin) != NULL) {
        split_input(input, command, arg);
    }
}
