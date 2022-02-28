#include "second_move.h"

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

bool second_move(FILE* inputf, Symbol* symbol_table, char* file_name)
{
	Symbol* s;
	bool error_flag = false;
	bool is_first_entry = true;
	char line[MAX_LINE_LENGTH+1];
	char label_name[MAX_LABEL_LENGTH];
	char c;
	int line_number = 0;

	fseek(inputf, 0, SEEK_SET); /* go back to the beginning of the file */

	while ((c = getc(inputf)) != EOF)
	{
		line[0] = c;
		fgets(&line[1], MAX_LINE_LENGTH, inputf); /* get a line */
		line_number++;

		if (is_comment(line) == true || is_empty(line) == true) /* ignore comments or empty lines */
				continue;

		switch (is_command(line, label_name, line_number))
		{
			case 1:
			case 2:
			case 3:
				continue; /* ignore .data .string or .extern commands */

			case 4: /* symbol defined as entry */

				s = search_symbol(symbol_table, label_name);

				if (s != NULL) /* symbol exist */
				{
					s -> entry = true;
					write_to_entries_file(s, file_name, is_first_entry);
					is_first_entry = false;
				}
					
				else 
				{
					printf("Line %d- Error: Undefined label \"%s\" was used\n", line_number, label_name);
					error_flag = true;
				}

				break;

			default: /* method sentence */
				break;
				
		}

	}
	
	if (error_flag == false)
		print_symbols(symbol_table);

	return (!error_flag);
}
