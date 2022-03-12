#include "second_move.h"

bool write_to_externals_file(Symbol* symbol, char* file_name, bool is_first_extern, int word_num)
{
	FILE* externals_file = NULL;

	if (is_first_extern) /* create the file */
	{
		strcat(file_name, ".ext");
		externals_file = fopen(file_name, "w");
	}

	else	/* append to the file */
		externals_file = fopen(file_name, "a");

	if (externals_file == NULL)
	{
		printf("Error: cannot open file: %s\n", file_name);
		return false;
	}
	
	fprintf(externals_file, "%s BASE ", symbol -> label_name);
	print_pre_zeros(externals_file, word_num);
	fprintf(externals_file, "%d\n", word_num);

	fprintf(externals_file, "%s OFFSET ", symbol -> label_name);
	print_pre_zeros(externals_file, word_num + 1);
	fprintf(externals_file, "%d\n\n", word_num + 1);				

	fclose(externals_file);
	return true;
}

bool write_to_entries_file(Symbol* symbol, char* file_name, bool is_first_entry)
{
	FILE* entries_file = NULL;

	if (is_first_entry)	/* create the file */
	{
		strcat(file_name, ".ent");
		entries_file = fopen(file_name, "w");
	}

	else	/* append to the file */
		entries_file = fopen(file_name, "a");

	if (entries_file == NULL)
	{
		printf("Error: cannot open file: %s\n", file_name);
		return false;
	}
	
	fprintf(entries_file, "%s, ", symbol -> label_name);

	print_pre_zeros(entries_file, symbol -> base_add);
	fprintf(entries_file, "%d, ", symbol -> base_add);

	print_pre_zeros(entries_file, symbol -> offset);
	fprintf(entries_file, "%d\n", symbol -> offset);

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
	int additional_from_orig_op;
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
			/* line with label operand- should push base and offset additional words */
			if (line_number == cur_return_to -> line_number)
			{
				additional_from_orig_op = get_operand_labels(line, orig_op, dest_op, line_number);

				if (strcmp(orig_op, "") != 0)
				{
					s = search_symbol(symbol_table, orig_op);

					if (s == NULL)
					{
						printf("Line %d- Error: Undefined label \"%s\" was used\n", line_number, orig_op);
						error_flag = true;
						cur_return_to = cur_return_to -> next;
						continue;
					}

					if (s -> attribute == EXTERNAL)
					{
						write_to_externals_file(s, file_name, is_first_extern, cur_return_to -> word -> index + BASE_ADDRESS);
						is_first_extern = false;
						/* set unknown words */
						cur_return_to -> word -> A = false;
						cur_return_to -> word -> E = true;
						cur_return_to -> word -> next -> A = false;
						cur_return_to -> word -> next -> E = true;
					}

					else
					{	/* set unknown words */
						cur_return_to -> word -> A = false;
						cur_return_to -> word -> R = true;
						cur_return_to -> word -> opcode = s -> base_add;
						cur_return_to -> word -> next -> A = false;
						cur_return_to -> word -> next -> R = true;
						cur_return_to -> word -> next -> opcode = s -> offset;
					}

				}

				if (strcmp(dest_op, "") != 0)
				{
					s = search_symbol(symbol_table, dest_op);

					if (s == NULL)
					{
						printf("Line %d- Error: Undefined label \"%s\" was used\n", line_number, dest_op);
						error_flag = true;
						cur_return_to = cur_return_to -> next;
						continue;
					}

					if (s -> attribute == EXTERNAL)
					{
						write_to_externals_file(s, file_name, is_first_extern,
									 cur_return_to -> word -> index + additional_from_orig_op + BASE_ADDRESS);
						is_first_extern = false;

						/* set unknown words */
						cur_return_to -> word -> A = false;
						cur_return_to -> word -> E = true;
						cur_return_to -> word -> next -> A = false;
						cur_return_to -> word -> next -> E = true;
					}

					else
					{	/* set unknown words */
						cur_return_to -> word -> A = false;
						cur_return_to -> word -> R = true;
						cur_return_to -> word -> opcode = s -> base_add;
						cur_return_to -> word -> next -> A = false;
						cur_return_to -> word -> next -> R = true;
						cur_return_to -> word -> next -> opcode = s -> offset;
					}

				}

				cur_return_to = cur_return_to -> next;
				continue;
			}
		}

		/* label define as entry */
		if (is_command(line, label_name, line_number, false) == ENTRY_COMMAND)
		{
			s = search_symbol(symbol_table, label_name);

			if (s != NULL) /* symbol exist */
			{	
				if (s -> attribute == EXTERNAL)
				{
					printf("Line %d- Error: Label \"%s\" define as extern and entry together\n", line_number, label_name);
					error_flag = true;
				}

				if (s -> entry == true)
					continue;

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

	destroy_words_to_return_list(returnTo);

	/* error on second move. should remove ext & ent output files */
	if (error_flag)
	{
		cut_end(file_name);
		remove(strcat(file_name, ".ext"));
		cut_end(file_name);
		remove(strcat(file_name, ".ent"));
	}

	return (!error_flag); /* return true if second move succeeded */
}
