#include "first_move.h"

/* return true if the first move succeeded or false if not */
bool first_move(char* file_name)
{
	FILE* inputf = NULL;
	Symbol* s = NULL;
	Symbol* symbol_table = NULL;
	Method* methods_list = NULL;
	WordsList* data_img = init_words_list();
	WordsList* code_img = init_words_list();
	char line[MAX_LINE_LENGTH+1];
	char label[MAX_LABEL_LENGTH];
	char method_name[5];
	char c;
	int line_number = 0;
	int ic = BASE_ADDRESS, dc = 0;
	int command_kind;
	int label_def;
	int new_words_num = 0;
	bool error_flag = false;

	inputf = fopen(file_name, "r");

	if (inputf == NULL)
	{
		printf("Error: cannot open file: %s\n", file_name);
		error_flag = true;
	}
	
	else
	{
		error_flag = !check_lines_size(inputf, MAX_LINE_LENGTH); 

		methods_list = init_methods_list();

		while ((c = getc(inputf)) != EOF)
		{
			line[0] = c;
			fgets(&line[1], MAX_LINE_LENGTH, inputf); /* get a line */
			line_number++;
			
			if (is_comment(line) == true || is_empty(line) == true) /* ignore comments or empty lines */
				continue;

			label_def = is_label_def(line, label, line_number);

			if (label_def == 1) /* there is label definition in the beginning of the line*/
			{
				if (is_legal_label(methods_list, label, line_number) == false) /* check if label name is legal */
				{	
					error_flag = true;
					continue;
				}

				switch ((command_kind = is_command(line, label, line_number))) /* its command sentence */
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

							new_words_num = conv_command(line, command_kind, line_number, data_img);
							if (new_words_num < 0)
								error_flag = true;

							dc += new_words_num;
						}

						else /* symbol is already exist */
						{
							printf("Line %d- Error: Label \"%s\" has already defined\n",line_number, label);
							error_flag = true;
						}

						break;

					case 3:
						 /* label define as external */

						printf("Line %d- Warning: A label was defined before external command. Ignore the label.\n",line_number);

						symbol_table = insert_symbol(symbol_table, label, 0, EXTERNAL, false);
						break;
					case 4:
						printf("Line %d- Warning: A label was defined before entry command. Ignore the label.\n", line_number);
						break;

					default:	 /* its not a command sentence */
						get_method_name(line, true, method_name);

						if (method_index(methods_list, method_name) != -1) /* method sentence */
						{
							s = search_symbol(symbol_table, label);
							if (s == NULL) /* new symbol */
							{
								symbol_table = insert_symbol(symbol_table, label, ic, CODE, false);

								new_words_num = conv_method(line, method_name, true, methods_list, line_number, code_img);
								if (new_words_num < 0)
									error_flag = true;

								ic += new_words_num;
							}
							
							else /* symbol is already exist */
							{
								printf("Line %d- Error: Label \"%s\" has already defined\n",line_number, label);
								error_flag = true;
							}

						}

						else
						{
							printf("Line %d- Error: method name is not exist\n", line_number);
							error_flag = true;
						}
						
				}
			}

			else if (label_def == 0)/* no label definition in the beginnig of the line */
			{
				switch (is_command(line, label, line_number))
				{
					case -1:
						error_flag = true;
						break;

					case DATA_COMMAND:
						new_words_num = conv_command(line, 1, line_number, data_img);
						if (new_words_num < 0)
							error_flag = true;

						dc += new_words_num;
						break;

					case STRING_COMMAND:
						new_words_num = conv_command(line, 2, line_number, data_img);
						if (new_words_num < 0)
							error_flag = true;

						dc += new_words_num;
						break;

					case EXTERN_COMMAND:      /* label define as external */
						if (is_legal_label(methods_list, label, line_number) == false) /* check if label name is legal */
						{	
							error_flag = true;
							continue;
						}

						symbol_table = insert_symbol(symbol_table, label, 0, EXTERNAL, false);
						break;

					case ENTRY_COMMAND:	     /* label define as entry */
						break;

					default:	 /* its not a command sentence */
						get_method_name(line, false, method_name);

						if (method_index(methods_list, method_name) != -1) /* method sentence */
						{
							new_words_num = conv_method(line, method_name, false, methods_list, line_number, code_img);
							if (new_words_num < 0)
								error_flag = true;

							ic += new_words_num;
						}
						
						else
						{
							printf("Line %d- Error: method name is not exist\n", line_number);
							error_flag = true;
						}
				}
			}

			else
			{
				error_flag = true;
			}
		}

		fix_symbol_table(symbol_table, ic); /* add the IC to the address of data symbols */
		if (error_flag == false) /* for debug */
			print_symbols(symbol_table);	
			print_words_list(data_img);
	}

	if (!error_flag)
		return second_move(inputf, symbol_table);

	printf("error in first move\n");
	return false;
}
