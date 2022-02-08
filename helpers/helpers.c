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

/* this function copy a string to another without the whitespace chars */
void clean_whitespace_chars(char* line, char* cleanLine)
{
	int i = 0;
	int j = 0;

	while (line[i] != '\0')
	{
		if (isspace(line[i]) == 0)
		{
			cleanLine[j] = line[i];
			j++;
		}
		i++;
	}

	cleanLine[j] = '\0';	
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


/* return 1 if there is a label definition in the current line and put the label name in "label_name".
 return 0 if there isn't and return -1 if there is error in label definition */
int is_label_def(char* line, char* label_name)
{
	int i = 0;

	line = trim(line);
		
	while (line[i] != ':')
	{
		if (line[i] == '\0')
		{
			label_name = NULL;
			return 0;
		}
		
		i++;
	}

	if (i > MAX_LABEL_LENGTH)
	{
		printf("Error: label name is too long\n");
		label_name = NULL;
		return -1;
	}
	
	for (i = 0; line[i] != ':'; i++)
	{
		label_name[i] = line[i];
	}

	label_name[i] = '\0';

	if (isupper(label_name[0]) || islower(label_name[0]))
	{
		return 1;
	}

	printf("Error: a label name must begin with an alphabetic character\n");
	label_name = NULL;
	return -1;
}

/* return 1-4 if this is a command sentence, 0 if not and -1 if there is an error in the command name.
   if its external or entry command, put the label name in "label_name" */
int is_command(char* line, char* label_name)
{
	int i = 0, j = 0;
	
	while (line[i] != '.')
	{
		if (line[i] == '\0')
		{
			return 0;
		}
		
		i++;
	}

	if (strncmp(&line[i + 1], "data ", 5) == 0)
	{
		return 1;
	}

	if (strncmp(&line[i + 1], "string ", 7) == 0)
	{
		return 2;
	}

	if (strncmp(&line[i + 1], "extern ", 7) == 0)
	{
		i =+ 8;
		while (isspace(line[i]))
		{
			i++;
		}

		while (line[i] != '\0')
		{
			if (j >= MAX_LABEL_LENGTH)
			{
				printf("Error: label name is too long\n");
				return -1;
			}

			label_name[j] = line[i];
			j++, i++;
		}

		label_name[j] = '\0';
		
		if (isupper(label_name[0]) || islower(label_name[0]))
		{
			return 3;
		}

		printf("Error: a label name must begin with an alphabetic character\n");
		return -1;
	}

	if (strncmp(&line[i + 1], "entry ", 6) == 0)
	{
		i =+ 7;
		while (isspace(line[i]))
		{
			i++;
		}

		while (line[i] != '\0')
		{
			if (j >= MAX_LABEL_LENGTH)
			{
				printf("Error: label name is too long\n");
				return -1;
			}

			label_name[j] = line[i];
			j++, i++;
		}

		label_name[j] = '\0';
		
		if (isupper(label_name[0]) || islower(label_name[0]))
		{
			return 4;
		}

		printf("Error: a label name must begin with an alphabetic character\n");
		return -1;
	}

	printf("Command name is not exist\n");
	return -1;
}

bool is_comment(char* line)
{
	line = trim(line);

	return (line[0] == ';');
}

bool is_empty(char* line)
{
	line = trim(line);

	return (strcmp(line, "") == 0);
}

char* cut_as(char* str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		if (strcmp(&str[i], ".as") == 0)
			str[i] = '\0';
		i++;
	}
	return str;
}

/* get a line and return the name of the method in the line (can be illegal method name). is_label_first is true if the beginning of the line is a label definition */
void get_method_name(char* line, bool is_label_first, char* method_name)
{
	int i = 0, j = 0;

	if (is_label_first)
		for (; line[i] != ':'; i++);
	
	for (; isspace(line[i]); i++);

	method_name = line + i;
}
