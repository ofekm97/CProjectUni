#include "second_move.h"

bool second_move(FILE* inputf, Symbol* symbol_table)
{
	bool error_flag = false;
	char line[MAX_LINE_LENGTH+1];
	char c;
	int line_number = 0;

	fseek(inputf, 0, SEEK_SET); /* go back to the beginning of the file */

	while ((c = getc(inputf)) != EOF)
	{
		line[0] = c;
		fgets(&line[1], MAX_LINE_LENGTH, inputf); /* get a line */
		line_number++;
			


	}
	
	if (error_flag == false)
		print_symbols(symbol_table);

	return (!error_flag);
}
