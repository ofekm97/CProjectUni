#include "methods.h"

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
	
	if (command_list == NULL) {
	        printf("method list is null, returning -1");
        return -1;
    }
    for (; i < AMOUNT_OF_METHODS; i++)
    {
        current = command_list[i];
        if (memcmp(word, current.name, current.name_size - 1) == 0)
        {
            last_char = *(word + current.name_size);
            if (isspace(last_char) || last_char == '\0') {
                return i;
            }
        }
    }
    return -1;
}
