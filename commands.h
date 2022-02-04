#pragma once

#include <string.h>

#define AMOUNT_OF_COMMANDS (16)

typedef struct Command
{
    char *command_name;
    int command_name_size;
    int group_num;
    int opcode;
    int func;
    int src_addressing_method;
    int dest_addressing_method;
} Command;

Command *init_commands_list();

void destriy_commands_list(Command *commands_list);

int command_index(Command *command_list, char *word);
