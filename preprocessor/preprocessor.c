#include "preprocessor.h"

/* this function return 1 if string is a macro definition line or 0 if not */
int is_macro_def(char* line, char* name)
{
	char cleanLine[MAX_LINE_LENGTH];

	clean_whitespace_chars(line, cleanLine);

	if (strncmp("macro", cleanLine, 5) == 0)
	{
		strcpy(name, &cleanLine[5]);
		return 1;
	}
	return 0;
}

/* this function copy the macro contest to macroText  */
void get_macro_text(char* macroText, FILE* inputf)
{
	char line[MAX_LINE_LENGTH] = "";
	char cleanLine[MAX_LINE_LENGTH] = "";
	
	while (strcmp("endm", cleanLine) != 0)
	{
		strcat(macroText, line);		
		fgets(line, MAX_LINE_LENGTH + 1, inputf);
		clean_whitespace_chars(line, cleanLine);
	}
}

/* this function return the macro that called in the current line or null if its not macro call line */
Macro* is_macro_call(Macro* m, char* line)
{
	char cleanLine[MAX_LINE_LENGTH];

	clean_whitespace_chars(line, cleanLine);

	return is_macro_name(m, cleanLine);
}

/* main function of the preprocessor. get a file.as and creat file.am with spread macros */
void span_macros(char* fileName)
{
	Macro* macrosTable = NULL;
	Macro* m = NULL;
	FILE* inputf = NULL;
	FILE* outputf = NULL;
	char line[MAX_LINE_LENGTH+1];
	char macroName[MAX_MACRO_NAME_LENGTH];
	char macroText[6 * MAX_LINE_LENGTH];
	char fileNameCopy[MAX_FILE_NAME_LENGTH];
	char c;

	strcpy(fileNameCopy, fileName); 

	inputf = fopen(strcat(fileName, ".as"), "r");

	if (inputf == NULL)
	{
		printf("cannot open file: %s\n", fileName);
	}
	
	else
	{
		outputf = fopen(strcat(fileNameCopy, ".am"), "w");
	
		while ((c = getc(inputf)) != EOF)
		{
			if (c == '\n')
				continue;

			line[0] = c;
			fgets(&line[1], MAX_LINE_LENGTH, inputf);

			m = is_macro_call(macrosTable, line);
		
			if (m != NULL)
			{
				fprintf(outputf, "%s", m -> macroText);
			}
			
			else if (is_macro_def(line, macroName) == 1)
			{
				strcpy(macroText, "");
				get_macro_text(macroText, inputf);
				macrosTable = insert_macro(macrosTable, macroName, macroText);
			}
			
			else
			{
				fprintf(outputf, "%s", line);
			}

		}
		
		destroy_macro_table(macrosTable);
		fclose(inputf);
		fclose(outputf);
	}


}
