#include "second_move.h"

bool second_move(char* file_name, Symbol* symbol_table)
{
	FILE* inputf = fopen(file_name, "r");
	bool error_flag = false;
	char line[MAX_LINE_LENGTH+1];
	char c;
	int line_number = 0;

	if (inputf == NULL)
	{
		printf("Error: cannot open file: %s\n", file_name);
		error_flag = true;
	}
	
	else
	{
		while ((c = getc(inputf)) != EOF)
		{
			line[0] = c;
			fgets(&line[1], MAX_LINE_LENGTH, inputf); /* get a line */
			line_number++;
			


		}
	}

	if (error_flag == false)
		print_symbols(symbol_table);

	return (!error_flag);
}
