#include "preprocessor/preprocessor.h"
#include "symbols/first_move.h"
#include "symbols/second_move.h"

int main(int argc, char *argv[])
{
	int i = 1;
	char file_name[MAX_FILE_NAME_LENGTH];

	for (; i < argc; i++)
	{
		strcpy(file_name, argv[i]);

		if (span_macros(file_name))
		{
			cut_end(file_name);
			first_move(strcat(file_name, ".am"));
		}

		printf("\n");
	}

	return 0;
}
