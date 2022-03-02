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

bool add_additional_words(OpperandInfo *info, WordsList *words_list, WordsToReturnToList *returnTo, int line_number, int *words_added_count)
{
	bool noErrors = true;
	returnTo = info->return_to_me ? returnTo : NULL;

	if(info->addressing_method == NO_OPERAND)
	{
		info->addressing_method = 0; 
		return true;
	}

	/* REG_DIRECT is the only one without additional words */
	if (info->addressing_method == REG_DIRECT)
	{
		return noErrors;
	}
	/* this needs to be changed accoding to is external and so.. */
	noErrors &= create_data_word(words_list, true, false, false, info->additional_first_word, line_number, returnTo);
	(*words_added_count)++;
	/* REG_DIRECT is the only one with one additional word */
	if (info->addressing_method == IMMEDIATE)
	{
		return noErrors;
	}
	noErrors &= create_data_word(words_list, true, false, false, info->additional_second_word, line_number, NULL);
	(*words_added_count)++;
	return noErrors;
}

bool handle_operands_info(Method *method, OpperandInfo *orig_info, OpperandInfo *dest_info, WordsList *words_list, WordsToReturnToList *returnTo, int line_number, int *words_added_count)
{
	bool noErrors = true;
	/* add the first word with the opcode */
	noErrors &= create_data_word(words_list, true, false, false, method->opcode, line_number, NULL);

	if (!noErrors)
		return noErrors;

	(*words_added_count)++;
	/* group 3 has only 1 word (opcode) */
	if (method->group_num == 3)
	{
		return noErrors;
	}
	/* add the second word with the func and regs and addressing methods */
	noErrors &= create_func_word(words_list, true, false, false,
								 method->func, orig_info->reg_num, orig_info->addressing_method,
								 dest_info->reg_num, dest_info->addressing_method);
	(*words_added_count)++;
	/* add the third word, beacuse labe need to return to it in the future */
	noErrors &= add_additional_words(orig_info, words_list, returnTo, line_number, words_added_count);
	noErrors &= add_additional_words(dest_info, words_list, returnTo, line_number, words_added_count);
	return noErrors;
}

void clean_info(OpperandInfo *info) {
	info->return_to_me = false;
	info->reg_num = 0;
	info->addressing_method = 0;
	info->additional_first_word = 0;
	info->additional_second_word = 0;
}

int conv_method(char *line, char *method, bool is_label_first, Method *methods_list, int line_number, WordsList *words_list, WordsToReturnToList *returnTo)
{
	char orig_op[MAX_LINE_LENGTH + 1], dest_op[MAX_LINE_LENGTH + 1];
	int ret_val = 0;
	Method *cur_method;
	OpperandInfo *orig_info = (OpperandInfo *)malloc(sizeof(OpperandInfo));
	OpperandInfo *dest_info = (OpperandInfo *)malloc(sizeof(OpperandInfo));
	clean_info(orig_info);
	clean_info(dest_info);

	/* operands format error */
	if (split_operands(line, is_label_first, orig_op, dest_op, line_number) == false)
	{
		goto cleanup;
	}

	strcpy(orig_op, trim(orig_op)); /* clean whitespaces */
	strcpy(dest_op, trim(dest_op));

	cur_method = methods_list + method_index(methods_list, method);

	if (!check_operands_number(cur_method, orig_op, dest_op))
	{
		printf("Line %d- Error: Number of operands does not match the method type\n", line_number);
		goto cleanup;
	}

	get_addresing_method(orig_op, orig_info, line_number);
	get_addresing_method(dest_op, dest_info, line_number);

	if (!(is_valid_addressing(cur_method, orig_info->addressing_method, true) && is_valid_addressing(cur_method, dest_info->addressing_method, false)))
	{
		printf("Line %d- Error: Operand addressing method does not match the method type\n", line_number);
		goto cleanup;
	}

	handle_operands_info(cur_method, orig_info, dest_info, words_list, returnTo, line_number, &ret_val);

cleanup:
	if (orig_info)
		free(orig_info);
	if (dest_info)
		free(dest_info);
	return ret_val;
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

				if (create_data_word(words_list, true, false, false, data_value, line_number, NULL))
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
			if (create_data_word(words_list, true, false, false, (int)(line[i]), line_number, NULL))
			{
				words_num++;
			}
		}

		if (create_data_word(words_list, true, false, false, (int)('\0'), line_number, NULL))
		{
			words_num++;
		}
	}

	return words_num;
}
