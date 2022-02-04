/*#include "preprocessor.c"

#include "helpers.c"
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
#include "commands_tester.c"
*/

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

Command *init_commands_list()
{
    int i = 0;
    Command *commands_list;
    Command *current;

    char *commands_names[AMOUNT_OF_COMMANDS] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"};
    int group_num[AMOUNT_OF_COMMANDS] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3};
    int opcodes[AMOUNT_OF_COMMANDS] = {0, 1, 2, 2, 4, 5, 5, 5, 5, 9, 9, 9, 12, 13, 14, 15};
    int funcs[AMOUNT_OF_COMMANDS] = {0, 0, 10, 11, 0, 10, 11, 12, 13, 10, 11, 12, 0, 0, 0, 0};
    int src_addressing_methods[AMOUNT_OF_COMMANDS] = {15, 15, 15, 15, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int dest_addressing_methods[AMOUNT_OF_COMMANDS] = {14, 15, 14, 14, 14, 14, 14, 14, 14, 6, 6, 6, 14, 15, 0, 0};

    commands_list = (Command *)calloc(sizeof(Command), AMOUNT_OF_COMMANDS);
    if (commands_list != NULL)
    {
        for (; i < AMOUNT_OF_COMMANDS; i++)
        {
            current = (commands_list + i);

            current->command_name_size = strlen(commands_names[i]);
            current->command_name = (char *)malloc(strlen(commands_names[i]));
            if (current->command_name != NULL)
            {

                strcpy(current->command_name, commands_names[i]);
            }
            current->group_num = group_num[i];
            current->opcode = opcodes[i];
            current->func = funcs[i];
            current->src_addressing_method = src_addressing_methods[i];
            current->dest_addressing_method = dest_addressing_methods[i];
        }
    }

    return commands_list;
}

void destriy_commands_list(Command *commands_list)
{
    int i = 0;

    for (; i < AMOUNT_OF_COMMANDS; i++)
    {
        if ((commands_list + i) != NULL)
        {
            if ((commands_list + i)->command_name != NULL)
            {
                free((commands_list + i)->command_name);
            }
            free((commands_list + i));
        }
    }
}

int command_index(Command *command_list, char *word)
{
    Command current;
    int i = 0;
    for (; i < AMOUNT_OF_COMMANDS; i++)
    {
        current = command_list[i];
        if (strcmp(word, current.command_name) == 0)
        {
            return i;
        }
    }
    return -1;
}

char *words_to_test[20] =
    {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "ofek", "yarin", "mov1", "mov "};

void test_commands_list()
{
    int i = 0;
    Command *list = init_commands_list();
    char *word;

    for (; i < 20; i++)
    {
        word = words_to_test[i];
        printf("%s: %d\n", word, command_index(list, word));
    }
    return;
}

int main(int argc, char *argv[])
{
    test_commands_list();

    return 0;
}
