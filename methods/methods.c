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
    int src_addressing_methods[AMOUNT_OF_METHODS] = {15, 15, 15, 15, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    int dest_addressing_methods[AMOUNT_OF_METHODS] = {14, 15, 14, 14, 14, 14, 14, 14, 14, 6, 6, 6, 14, 15, -1, -1};

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
            if (isspace(last_char) || last_char == '\0')
            {
                return i;
            }
        }
    }
    return -1;
}

bool is_legal_label(Method* command_list, char* label)
{
	int i = 0;

	while(label[i] != '\0')
	{
		if (isalnum(label[i]) == 0)
		{
			printf("Error: Label name has only alpha-numeric characters\n");
			return false;
		}

		i++;
	}

	if (method_index(command_list, label) > 0)
	{
		printf("Error: Label name cannot be the same as method name\n");
		return false;
	}

	if (get_reg_number(label, &i))
	{
		printf("Error: Label name cannot be the same as register name\n");
		return false;
	}

	return true;
}

bool is_valid_addressing(Method *method, Addressing_Methods operand_type, bool is_source)
{
    int bit_wise_addressing = 1 << operand_type;

    if (operand_type == NO_OPERAND)
	return true;

    return (bool)(is_source ? (method->src_addressing_method & bit_wise_addressing) : (method->dest_addressing_method & bit_wise_addressing));
}

bool get_index_or_direct_addressing(char *operand, Addressing_Methods *addressing_method)
{
    int braces_index = 0, reg_number = -1;
    char reg[4];
    char *temp = operand;

    while (*(temp))
    {
        if (*(temp) == '[')
            break;
        temp++;
        braces_index++;
    }

    if ((*temp))
    {
        memcpy(reg, temp + 1, 3);
        reg[3] = '\0';

        if (get_reg_number(reg, &reg_number))
        {
            if (10 <= reg_number || reg_number <= 15)
            {
                *addressing_method = INDEX;
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        *addressing_method = DIRECT;
    }
    return true;
}

bool get_addresing_method(char *operand, Addressing_Methods *addressing_method)
{
    signed int reg_number = -1;

    if (is_empty(operand))
    {
	*addressing_method = NO_OPERAND;
	 return true;
    }

    if (get_reg_number(operand, (signed int *)&reg_number))
    {
        *addressing_method = REG_DIRECT;
        return true;
    }

    if (*operand == '#')
    {
        if (get_number_from_string(operand + 1, (signed int *)addressing_method))
        {
            *addressing_method = IMMEDIATE;
            return true;
        }
    }

    if (get_index_or_direct_addressing(operand, addressing_method))
    {
        return true;
    }

    return false;
}

bool check_operands_number(Method *method, char origin_operand[MAX_LINE_LENGTH+1], char dest_operand[MAX_LINE_LENGTH+1])
{
    bool noErrors = true;

	if (is_empty(origin_operand)) 
        	noErrors &= (bool)(method->src_addressing_method == -1);
	else
		noErrors &= (bool)(method->src_addressing_method != -1);
	

	if (is_empty(dest_operand))
	        noErrors &= (bool)(method->dest_addressing_method == -1);
	else
		noErrors &= (bool)(method->dest_addressing_method != -1);

    return noErrors;
}
