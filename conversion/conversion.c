#include "conversion.h"

bool get_number_from_data_command(char *str, int *value)
{
	int i = 0;
	int amount = sscanf(str, "%d", value);

	if (amount == 0)
	{
		return false;
	}

	for (; isspace(str[i]) != 0; i++)
		;

	if (str[i] == '-')
		i++;

	for (; '0' <= str[i] && str[i] <= '9'; i++)
		;

	for (; str[i] != ',' && str[i] != '\0'; i++)
	{
		if (isspace(str[i]) == 0)
			return false;
	}

	return true;
}

bool check_string_format(char *line)
{
	int i = 0;
	int counter = 0;

	if (line[0] != '"')
		return false;

	while (line[i] != '\0')
	{
		if (line[i] == '"')
			counter++;
		i++;
	}

	if (line[i - 1] != '"')
		return false;

	if (counter != 2)
		return false;

	return true;
}

int conv_method(char *line, char *method, bool is_label_first, Method *methods_list, int line_number, WordsList *words_list)
{
	char orig_op[MAX_LINE_LENGTH + 1], dest_op[MAX_LINE_LENGTH + 1];
	Addressing_Methods orig_addressing_method = -1;
	Addressing_Methods dest_addressing_method = -1;
	Method *cur_method;

	if (split_operands(line, is_label_first, orig_op, dest_op, line_number) == false) /* operands format error */
		return -1;

	strcpy(orig_op, trim(orig_op)); /* clean whitespaces */
	strcpy(dest_op, trim(dest_op));

	cur_method = methods_list + method_index(methods_list, method);

	if (!check_operands_number(cur_method, orig_op, dest_op))
	{
		printf("Line %d- Error: Number of operands does not match the method type\n", line_number);
		return -1;
	}

	get_addresing_method(orig_op, &orig_addressing_method, line_number);
	get_addresing_method(dest_op, &dest_addressing_method, line_number);

	if (!(is_valid_addressing(cur_method, orig_addressing_method, true) && is_valid_addressing(cur_method, dest_addressing_method, false)))
	{
		printf("Line %d- Error: Operand addressing method does not match the method type\n", line_number);
		return -1;
	}

	/* push words */

	return 1;
}

int conv_command(char *line, int command_kind, int line_number, WordsList *words_list)
{
	int i = 0, data_value = 0, words_num = 0;

	if (command_kind == DATA_COMMAND)
	{
		for (; line[i] != '.'; i++)
			;
		i += 4;
		while (line[i])
		{
			i++;
			for (; isspace(line[i]) != 0; i++)
				; /* skip spaces before the number */

			while (line[i] != '\0')
			{
				if (get_number_from_data_command(line + i, &data_value) == false)
				{
					printf("Line %d- Error: Data format is illegal\n", line_number);
					return -1;
				}

				/* a word can hold integers between -2047 to 2048 (16 bits) */
				if (data_value < MIN_INTEGER || MAX_INTEGER < data_value)
				{
					printf("Line %d- Error: Integer is too large\n", line_number);
					return -1;
				}

				for (; line[i] != ',' && line[i] != '\0'; i++)
					;
				i++;

				if (create_data_word(words_list, true, false, false, data_value))
					words_num++;
			}

			if (line[i - 1] == ',') /* comma after the last operand */
			{
				printf("Line %d- Error: Data format is illegal\n", line_number);
				return -1;
			}
		}
	}

	if (command_kind == STRING_COMMAND) /* string */
	{
		for (; line[i] != '.'; i++)
			;
		i += 7;
		line = trim(line + i);

		if (check_string_format(line) == false)
		{
			printf("Line %d- Error: String format is illegal\n", line_number);
			return -1;
		}

		for (i = 1; line[i] != '"'; i++)
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
