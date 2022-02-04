#pragma once

#include <string.h>

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

Method *init_methods_list();

void destroy_methods_list(Method *methods_list);

int method_index(Method *methods_list, char *word);
