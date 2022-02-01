#include "helpers.h"

int get_reg_number(char *reg_name)
{
    char temp;
    int ret_value = 0;
    int amount = 0;
    reg_name = trim(reg_name);
    if (reg_name == NULL)
    {
        return -1;
    }
    if (reg_name[0] != 'r')
    {
        return -1;
    }
    amount = sscanf(reg_name + 1, "%d%c", &ret_value, &temp);
    if (amount == 1)
    {
        if (ret_value <= 15 && 0 <= ret_value)
            return ret_value;
    }
    return -1;
}

/* Mutate the str string */
char *trim(char *str)
{
    char *end;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == 0)
        return str;

    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end))
        end--;

    end[1] = '\0';

    return str;
}