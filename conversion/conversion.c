#include "conversion.h"

int get_first_value(char* line) /* not final */
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

	

	return 1;
}

int conv_command(char* line,int command_kind, bool is_label_first)
{
	int i = 0;
	int words_num = 0;

	if (command_kind == 1) /* data */
	{
		for (; line[i] != '.'; i++);
		i += 5;
		for (; isspace(line[i]) != 0; i++);

		/* push words */

		return 1;
	}

	if (command_kind == 2) /* string */
	{
		if (quot_marks_counter(line) != 2)
		{
			printf("Error: String format is illegal\n");
			return 0;
		}

		for (; line[i] != '"'; i++);
		for (i++; line[i] != '"'; i++)
		{
			/* push word- line[i] */
			words_num++;
		}
			/* push word- '\0' */
			words_num++;
	}

	return words_num;
}
