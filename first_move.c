#include "first_move.h"

/* return true if the first move succeeded or false if not */
bool first_move(char* file_name)
{
	FILE* inputf = NULL;
	Symbol* symbol_table = NULL;
	Symbol* s = NULL;
	char line[MAX_LINE_LENGTH];
	char label[MAX_LABEL_LENGTH];
	char c;
	int ic = BASE_ADDRESS, dc = 0;
	int base = 0, offset = 0;
	int label_def;
	bool error_flag = false;

	inputf = fopen(file_name, "r");

	if (inputf == NULL)
	{
		printf("cannot open file: %s\n", file_name);
		error_flag = true;
	}
	
	else
	{
		c = getc(inputf);
		while (c != EOF)
		{
			line[0] = c;
			fgets(&line[1], MAX_LINE_LENGTH, inputf); /* get a line */ 
			
			if (is_comment(line) == true || is_empty(line) == true) /* ignore comments or empty lines */
			{
				c = getc(inputf);	
				continue;
			}

			label_def = is_label_def(line, label);
			if (label_def == 1) /* there is label definition in the beginning of the line*/
			{
				switch (is_command(line, label)) /* its command sentence */
				{
					case -1:
						error_flag = true;
						break;
					
					case 1:
					case 2:
						s = search_symbol(symbol_table, label);
						if (s == NULL) /* new symbol */
						{
							symbol_table = insert_symbol(symbol_table, label, dc, DATA, false);
							dc++;
						}

						else /* symbol already exist. set it */
						{
							s -> value = dc;
							s -> attribute = DATA;
							get_base_and_offset(s -> value, &base, &offset);
							s -> base_add = base;
							s -> offset = offset;
							dc++;
						}

						break;

					case 3:
						printf("Error: A label was defined before external command.\n");
						error_flag = true;
						break;
					case 4:
						printf("Error: A label was defined before entry command.\n");
						error_flag = true;
						break;
				}
			}

			else if (label_def == 0)/* no label definition in the beginnig of the line*/
			{
				switch (is_command(line, label))
				{
					case -1:
						error_flag = true;
						break;

					case 1:
						break;

					case 2:
						break;

					case 3:      /* label define as external */
						symbol_table = insert_symbol(symbol_table, label, 0, EXTERNAL, false);
						dc++;
						break;

					case 4:
						s = search_symbol(symbol_table, label);
						if (s != NULL) /* symbol already exist */
						{
							s -> entry = true;
						}
					
						else /* new symbol */
						{
							symbol_table = insert_symbol(symbol_table, label, 0, DONT_KNOW, true);
						}

						break;
				}
			}

			else
			{
				error_flag = true;
			}

			c = getc(inputf);
		}

		fix_symbol_table(symbol_table, ic); /* add the IC to the address of data symbols */
		print_symbols(symbol_table);	
	}
	return (!error_flag);
}
