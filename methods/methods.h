#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef METHODS
	#define METHODS
	#include "../helpers/helpers.h"
#endif

#define AMOUNT_OF_METHODS (16)
#define MAX_LINE_LENGTH (80)

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


typedef enum Addressing_Methods
{
    IMMEDIATE = 0,
    DIRECT = 1,
    INDEX = 2,
    REG_DIRECT = 3
} Addressing_Methods;

Method *init_methods_list();

void destroy_methods_list(Method *methods_list);

int method_index(Method *methods_list, char *word);

bool check_addressing_method(Method *method, char origin_operand[MAX_LINE_LENGTH+1], char dest_operand[MAX_LINE_LENGTH+1]);
