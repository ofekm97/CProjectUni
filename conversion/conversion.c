#include "conversion.h"

bool get_number_from_data_command(char* str, int* value) 
{
	int i = 0;
	int amount = sscanf(str, "%d", value);

	if (amount == 0)
  	{
        	return false;
    	}

	for (; isspace(str[i]) != 0 ; i++);

	if (str[i] == '-')
		i++;

	for (; '0' <= str[i] && str[i] <= '9' ; i++);

	for (; str[i] != ',' && str[i] != '\0'; i++)
	{
		if (isspace(str[i]) == 0)
			return false;
	}
	
	return true;
}

int quot_marks_counter(char* line)
{
	int i = 0;
	int counter = 0;

	while (line[i] != '\0')
	{
		if (line[i] == '"')
			counter++;
		i++;
	}
	return counter;
}

int conv_method(char* line, char* method, bool is_label_first)
{
	char orig_op[MAX_LINE_LENGTH+1], dest_op[MAX_LINE_LENGTH+1];

	if (split_operands(line, is_label_first, orig_op, dest_op) == false) /* operands format error */
		return -1;

	strcpy(orig_op,trim(orig_op));
	strcpy(dest_op,trim(dest_op));
	

	return 1;
}

int conv_command(char* line,int command_kind, bool is_label_first)
{
	int i = 0;
	int words_num = 0;
	int data_value = 0;

	if (command_kind == 1) /* data */
	{
		for (; line[i] != '.'; i++);
		i += 5;
		for (; isspace(line[i]) != 0; i++);

		while (line[i] != '\0')
		{
			if (get_number_from_data_command(line + i, &data_value) == false)
			{
				printf("Error: Data format is illegal\n");
				return -1;
			}

			/* a word can hold integers between -2047 to 2048 (16 bits) */
			if (data_value < MIN_INTEGER || MAX_INTEGER < data_value)
			{
				printf("Error: Integer is too large\n");
				return -1;
			}
			
			for (; line[i] != ',' && line[i] != '\0'; i++);
			i++;

			/* push data_value */

			words_num++;
		}

		return words_num;
	}

	if (command_kind == 2) /* string */
	{
		if (quot_marks_counter(line) != 2)
		{
			printf("Error: String format is illegal\n");
			return -1;
		}

		for (; line[i] != '"'; i++);
		for (i++; line[i] != '"'; i++)
		{
			/* push word- Ascii(line[i]) */
			words_num++;
		}
			/* push word- '\0' */
			words_num++;
	}

	return words_num;
}
