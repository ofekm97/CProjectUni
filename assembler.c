/*#include "preprocessor.c"

#include "helpers.c"
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/*
#include "commands_tester.c"
*/


#define AMOUNT_OF_METHODS (16)

typedef struct Method
{
    char *name;
    int name_size;
    int group_num;
    int opcode;
    int func;
    int src_addressing_method;
    int dest_addressing_method;
} Method;

Method *init_methods_list()
{
    int i = 0;
    Method *commands_list;
    Method *current;

    char *commands_names[AMOUNT_OF_METHODS] = {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop"};
    int group_num[AMOUNT_OF_METHODS] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3};
    int opcodes[AMOUNT_OF_METHODS] = {0, 1, 2, 2, 4, 5, 5, 5, 5, 9, 9, 9, 12, 13, 14, 15};
    int funcs[AMOUNT_OF_METHODS] = {0, 0, 10, 11, 0, 10, 11, 12, 13, 10, 11, 12, 0, 0, 0, 0};
    int src_addressing_methods[AMOUNT_OF_METHODS] = {15, 15, 15, 15, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int dest_addressing_methods[AMOUNT_OF_METHODS] = {14, 15, 14, 14, 14, 14, 14, 14, 14, 6, 6, 6, 14, 15, 0, 0};

    commands_list = (Method *)calloc(sizeof(Method), AMOUNT_OF_METHODS);
    if (commands_list != NULL)
    {
        for (; i < AMOUNT_OF_METHODS; i++)
        {
            current = (commands_list + i);

            current->name_size = strlen(commands_names[i]);
            current->name = (char *)malloc(strlen(commands_names[i]));
            if (current->name != NULL)
            {

                strcpy(current->name, commands_names[i]);
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

void destroy_methods_list(Method *commands_list)
{
    int i = 0;

    for (; i < AMOUNT_OF_METHODS; i++)
    {
        if ((commands_list + i) != NULL)
        {
            if ((commands_list + i)->name != NULL)
            {
                free((commands_list + i)->name);
            }
        }
    }
    free(commands_list);
}

int method_index(Method *command_list, char *word)
{
    Method current;
    char last_char;
    int i = 0;
    for (; i < AMOUNT_OF_METHODS; i++)
    {
        current = command_list[i];
        if (memcmp(word, current.name, current.name_size - 1) == 0)
        {
            last_char = *(word + current.name_size);
            printf("current.name_size: %d,  ", current.name_size);
            if (isspace(last_char) || last_char == '\0') {
                return i;
            }
        }
    }
    return -1;
}

char *words_to_test[20] =
    {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "ofek", "yarin", "mov1", "mov "};

void test_commands_list()
{
    int i = 0;
    Method *list = init_methods_list();
    char *word;

    for (; i < 20; i++)
    {
        word = words_to_test[i];
        printf("%s: %d\n", word, method_index(list, word));
    }
    
    destroy_methods_list(list);
    return;
}

int main(int argc, char *argv[])
{
    test_commands_list();

    return 0;
}
