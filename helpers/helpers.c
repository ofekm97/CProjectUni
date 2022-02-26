#include "helpers.h"

bool check_lines_size(FILE* file, int max)
{
	int length = 0, line_number = 1;
	char c;
 
	while ((c = getc(file)) != EOF)
	{
		if (c == '\n')
		{
			length = 0;
			line_number++;
			continue;
		}

		length++;

		if (length > max)
		{
			printf("Error: Line %d is longer than %d\n", line_number, max);
			fseek(file, 0, SEEK_SET);
			return false;
		}
	}
	
	fseek(file, 0, SEEK_SET);
	return true;
}

bool get_reg_number(char *reg_name, int* ret_value)
{
    reg_name = trim(reg_name);
    if (reg_name == NULL)
    {
        return false;
    }
    if (reg_name[0] != 'r')
    {
        return false;
    }
	
    if (get_number_from_string(reg_name+1, ret_value, true))
    {
        if (*ret_value <= 15 && 0 <= *ret_value)
            return true;
    }
    return false;
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
	
	else
	{
		printf("Error: a label name must begin with an alphabetic character\n");
		label_name = NULL;
		return -1;
	}
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
		return DATA_COMMAND;
	}

	if (strncmp(&line[i + 1], "string ", 7) == 0)
	{
		return STRING_COMMAND;
	}

	if (strncmp(&line[i + 1], "extern ", 7) == 0)
	{
		i += 8;
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
			return EXTERN_COMMAND;
		}

		printf("Error: a label name must begin with an alphabetic character\n");
		return -1;
	}

	if (strncmp(&line[i + 1], "entry ", 6) == 0)
	{
		i += 7;
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
			return ENTRY_COMMAND;
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
	
	for (i++; isspace(line[i]); i++);

	while (isspace(line[i]) == 0 && line[i] != '\0')
	{
		if (j == 4)
		{
			method_name = NULL;
			return;
		}

		method_name[j] = line[i];
		i++, j++;
	}

	method_name[j] = '\0';

	if (strlen(method_name) == 4 && strcmp(method_name, "stop") != 0)
	{
		method_name = NULL;
		return;
	}
}

int commas_counter(char* line)
{
	int i = 0;
	int counter = 0;

	while (line[i] != '\0')
	{
		if (line[i] == ',')
		{
			counter++;
			
			if (line[i + 1] == ',') /* error. there are two commas in a row */
				return -1;

		}

		i++;
	}
	
	return counter;
}

bool check_operand(char* operand)
{
	int i = 0;

	for (; operand[i] != '\0'; i++)
	{
		if (isspace(operand[i]) != 0)
		{
			printf("unvalid operand\n");
			return false;
		}
	}

	return true;
}

bool split_operands(char* line, bool is_label_first, char* orig_op, char* dest_op)
{
	int i = 0, j = 0;
	int commas_num;

	strcpy(orig_op, ""), strcpy(dest_op, ""); /* initialize */

	if (is_label_first)
	{
		for (; line[i] != ':'; i++); /* skip the label */
		i++;
	}

	for (; isspace(line[i]) != 0; i++); /* skip the whitespaces */
	for (; isspace(line[i]) == 0; i++)  /* skip the method name */
	{
		if (line[i] == '\0') /* no operands */
			return true;
	}

	i++;
	for (; isspace(line[i]) != 0; i++); /* skip the whitespaces */
	
	if (line[i] == ',') /* comma before the first operand */
	{
		printf("Error: Comma location is illegal\n");
		return false;
	}

	if (strcmp(&line[i], "") == 0) /* no operands */
		return true;

	commas_num = commas_counter(&line[i]);

	if (commas_num == 0) /* 1 operand */
	{
		while (line[i] != '\0')
		{
			orig_op[j] = line[i];
			i++, j++;
		}
		
		orig_op[j] = '\0';
		orig_op = trim(orig_op);

		if (check_operand(orig_op) == false)
			return false;

		return true;
	}

	if (commas_num == 1) /* 2 operands */
	{
		while (line[i] != ',')
		{
			orig_op[j] = line[i];
			i++, j++;
		}

		orig_op[j] = '\0';
		i++;

		if (line[i] == '\0') /* comma after the last operand */
		{
			printf("Error: Comma location is illegal\n");
			strcpy(orig_op, "");
			return false;
		}
		
		j = 0;

		while (line[i] != '\0')
		{
			dest_op[j] = line[i];
			i++, j++;
		}
		
		dest_op[j] = '\0';
		orig_op = trim(orig_op);
		dest_op = trim(dest_op);

		if (check_operand(orig_op) == false || check_operand(dest_op) == false)
			return false;

		return true;
	}

	if (commas_num == -1)
	{
		printf("Error: Two commas in a row\n");
		return false;
	}
	
		/* more than 2 operands */
		printf("Error: Too much operands or commas\n");
		return false;
}

bool get_number_from_string(char* str, signed int* value, bool expect_comma) {
	char temp;
	int amount = sscanf(str, "%d%c", value, &temp);
	if (amount == 1 || (amount == 2 && (isspace(temp) || (expect_comma && temp == ','))))
    {
        return true;
    }
	return false;
}