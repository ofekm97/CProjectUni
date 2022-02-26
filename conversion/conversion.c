#include "conversion.h"

int get_first_value(char *line) /* not final */
{
	char str[MAX_DATA_LENGTH];
	int i = 0;

	for (; line[i] != ','; i++);

	if (i > MAX_DATA_LENGTH || (i > MAX_DATA_LENGTH - 1 && line[0] == '-'))
	{
		printf("Error: Integer is too large\n");
		return 2049;
	}

	for (i = 0; line[i] != ','; i++)
	{
		str[i] = line[i];
	}
	return atoi(str);
}

int quot_marks_counter(char *line)
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

int conv_method(char *line, char *method, bool is_label_first, WordsList *words_list)
{
	char orig_op[MAX_LINE_LENGTH + 1], dest_op[MAX_LINE_LENGTH + 1];

	if (split_operands(line, is_label_first, orig_op, dest_op) == false) /* operands format error */
		return -1;

	strcpy(orig_op, trim(orig_op));
	strcpy(dest_op, trim(dest_op));

	return 1;
}

int conv_command(char *line, int command_kind, bool is_label_first, WordsList *words_list)
{
	int i = 0, current_value = 0, words_num = 0;

	if (command_kind == DATA_COMMAND)
	{
		for (; line[i] != '.'; i++);
		i += 4;
		while (line[i])
		{
			i++;
			for (; isspace(line[i]) != 0; i++); /* skip spaces before the number */

			if (get_number_from_string(line + i, &current_value, true))
			{
				if (create_data_word(words_list, true, false, false, current_value))
					words_num++;
			}
			else
			{
				/* print error for no number */
			}
			for (; isspace(line[i]) == 0; i++)
			{ /* skip the number we just read */
				if (line[i] == '\0')
					break;
				else if (line[i] == ',')
				{ /* if reached a ',' can continue to the next number */
					break;
				}
			}

			for (; isspace(line[i]) != 0; i++); /* skip spaces after the number */
			/* if the next non space char is not a ',' or '\0' print error */
			if (line[i] != ',' && line[i] != '\0')
			{
				printf("the remaining string is: %s\n", line + i);
			}
		}

		return 1;
	}

	if (command_kind == STRING_COMMAND) /* string */
	{
		if (quot_marks_counter(line) != 2)
		{
			printf("Error: String format is illegal\n");
			return 0;
		}

		for (; line[i] != '"'; i++);
		for (i++; line[i] != '"'; i++)
		{
			if (create_data_word(words_list, true, false, false, (int)(line[i])))
			{
				words_num++;
			}
		}
		if (create_data_word(words_list, true, false, false, (int)('\0')))
		{
			words_num++;
		}
	}

	return words_num;
}
