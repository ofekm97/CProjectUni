#include "preprocessor/preprocessor.h"
#include "symbols/first_move.h"
#include "symbols/second_move.h"

int main(int argc, char* argv[])
{
	int i = 1;
	char file_name[MAX_FILE_NAME_LENGTH];

	for (; i < argc; i++)
	{
		strcpy(file_name, argv[i]);
		span_macros(file_name);
		first_move(strcat(cut_as(file_name), ".am"));
	}

	return 0;
}
