#include "first_move.h"

/* return true if the first move succeeded or false if not */
bool first_move(char* file_name)
{
	FILE* inputf = NULL;
	Symbol* symbol_table = NULL;
	Symbol* s = NULL;
	Method* methods_list = NULL;
	char line[MAX_LINE_LENGTH+1];
	char label[MAX_LABEL_LENGTH];
	char method_name[5];
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
		while ((c = getc(inputf)) != EOF)
		{
			line[0] = c;
			fgets(&line[1], MAX_LINE_LENGTH, inputf); /* get a line */ 
			
			if (is_comment(line) == true || is_empty(line) == true) /* ignore comments or empty lines */
			{
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
							dc++; /* shoud be: dc =+ number of new words from this line  */
						}

						else /* symbol already exist. set it */
						{
							s -> value = dc;
							s -> attribute = DATA;
							get_base_and_offset(s -> value, &base, &offset);
							s -> base_add = base;
							s -> offset = offset;
							dc++; /* shoud be: dc =+ number of new words from this line  */
						}

						break;

					case 3:
						printf("Warning: A label was defined before external command. Ignore the label.\n");
						break;
					case 4:
						printf("Warning: A label was defined before entry command. Ignore the label.\n");
						break;

					default:	 /* its not a command sentence */
						get_method_name(line, true, method_name);

						if (method_index(methods_list, method_name) != -1) /* method sentence */
						{
							symbol_table = insert_symbol(symbol_table, label, ic, CODE, false);
							ic++; /* shoud be: ic =+ number of new words from this line  */
						}

						else
						{
							printf("Error: method name \"%s\" is not exist\n", method_name);
							error_flag = true;
						}
						
				}
			}

			else if (label_def == 0)/* no label definition in the beginnig of the line */
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
						break;

					case 4:	     /* label define as entry */	
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

					default:	 /* its not a command sentence */
						get_method_name(line, false, method_name);
						
				}
			}

			else
			{
				error_flag = true;
			}

		}

		fix_symbol_table(symbol_table, ic); /* add the IC to the address of data symbols */
		print_symbols(symbol_table);	
	}
	return (!error_flag);
}
