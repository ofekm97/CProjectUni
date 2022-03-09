#include "second_move.h"

bool write_to_externals_file(Symbol* symbol, char* file_name, bool is_first_extern)
{
	FILE* externals_file = NULL;

	if (is_first_extern)
	{
		strcat(file_name, ".ext");
		externals_file = fopen(file_name, "w");
	}

	else
		externals_file = fopen(file_name, "a");

	if (externals_file == NULL)
	{
		printf("Error: cannot open file: %s\n", file_name);
		return false;
	}
										/* instead of 0 should be ic */
	fprintf(externals_file, "%s BASE %d\n%s OFFSET %d\n\n", symbol -> label_name, 0, symbol -> label_name, 0 + 1);

	fclose(externals_file);
	return true;
}

bool write_to_entries_file(Symbol* symbol, char* file_name, bool is_first_entry)
{
	FILE* entries_file = NULL;

	if (is_first_entry)
	{
		strcat(file_name, ".ent");
		entries_file = fopen(file_name, "w");
	}

	else
		entries_file = fopen(file_name, "a");

	if (entries_file == NULL)
	{
		printf("Error: cannot open file: %s\n", file_name);
		return false;
	}
	
	fprintf(entries_file, "%s, %d, %d\n", symbol -> label_name, symbol -> base_add, symbol -> offset);

	fclose(entries_file);
	return true;
}

bool second_move(FILE* inputf, Symbol* symbol_table, char* file_name, WordsToReturnToList* returnTo)
{
	Symbol* s = NULL;
	WordToReturnTo* cur_return_to = NULL;
	bool error_flag = false;
	bool is_first_entry = true;
	bool is_first_extern = true;
	char label_name[MAX_LABEL_LENGTH];
	char line[MAX_LINE_LENGTH+1];
	char orig_op[MAX_LINE_LENGTH + 1], dest_op[MAX_LINE_LENGTH + 1];
	char file_name_copy[MAX_FILE_NAME_LENGTH];
	char c;
	int line_number = 0;

	fseek(inputf, 0, SEEK_SET); /* go back to the beginning of the file */

	strcpy(file_name_copy, file_name);

	cur_return_to = returnTo -> first;

	while ((c = getc(inputf)) != EOF)
	{
		line[0] = c;
		fgets(&line[1], MAX_LINE_LENGTH, inputf); /* get a line */
		line_number++;

		if (is_comment(line) == true || is_empty(line) == true) /* ignore comments or empty lines */
				continue;

		if (cur_return_to != NULL)
		{
			if (line_number == cur_return_to -> line_number)
			{ 
				get_operand_labels(line, orig_op, dest_op, line_number);

				if (strcmp(orig_op, "") != 0)
				{
					s = search_symbol(symbol_table, orig_op);

					if (s == NULL)
					{
						printf("Line %d- Error: Undefined label \"%s\" was used\n", line_number, orig_op);
						error_flag = true;
						continue;
					}

					if (s -> attribute == EXTERNAL)
					{	
						write_to_externals_file(s, file_name, is_first_extern);
						is_first_extern = false;
					}
					/* change unknown words */
				}

				if (strcmp(dest_op, "") != 0)
				{
					s = search_symbol(symbol_table, dest_op);

					if (s == NULL)
					{
						printf("Line %d- Error: Undefined label \"%s\" was used\n", line_number, dest_op);
						error_flag = true;
						continue;
					}

					if (s -> attribute == EXTERNAL)
					{
						write_to_externals_file(s, file_name, is_first_extern);
						is_first_extern = false;
					}
					/* change unknown words */
				}

				cur_return_to = cur_return_to -> next;
				continue;
			}
		}

		if (is_command(line, label_name, line_number) == ENTRY_COMMAND)
		{
			s = search_symbol(symbol_table, label_name);

			if (s != NULL) /* symbol exist */
			{
				s -> entry = true;
				write_to_entries_file(s, file_name_copy, is_first_entry);
				is_first_entry = false;
			}
				
			else 
			{
				printf("Line %d- Error: Undefined label \"%s\" was used\n", line_number, label_name);
				error_flag = true;
			}
	
		}

	}	

	if (error_flag == false)
		print_symbols(symbol_table);

	return (!error_flag);
}
