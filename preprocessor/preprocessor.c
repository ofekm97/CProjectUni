#include "preprocessor.h"
#include <ctype.h>
#define MAX_FILE_NAME_LENGTH 31

/* this function copy a string to another without the whitespace chars */
void Clean_Whitespace_Chars(char* line, char* cleanLine)
{
	int i = 0;
	int j = 0;

	while (line[i] != '\0')
	{
		if (isspace(line[i]) == 0)
		{
			cleanLine[j] = line[i];
			j++;
		}
		i++;
	}

	cleanLine[j] = '\0';	
}

/* this function return 1 if string is a Macro definition line or 0 if not */
int Is_Macro_Def(char* line, char* name)
{
	char cleanLine[MAX_LINE_LENGTH];

	Clean_Whitespace_Chars(line, cleanLine);

	if (strncmp("macro", cleanLine, 5) == 0)
	{
		strcpy(name, &cleanLine[5]);
		return 1;
	}
	return 0;
}

/* this function copy the Macro contest to macroText  */
void Get_Macro_text(char* macroText, FILE* inputf)
{
	char line[MAX_LINE_LENGTH] = "";
	char cleanLine[MAX_LINE_LENGTH] = "";
	
	while (strcmp("endm", cleanLine) != 0)
	{
		strcat(macroText, line);		
		fgets(line, MAX_LINE_LENGTH + 1, inputf);
		Clean_Whitespace_Chars(line, cleanLine);
	}
}

/* this function return the Macro that called in the current line or null if its not Macro call line */
Macro* Is_Macro_Call(Macro* m, char* line)
{
	char cleanLine[MAX_LINE_LENGTH];

	Clean_Whitespace_Chars(line, cleanLine);

	return is_macro_name(m, cleanLine);
}

/* main function of the preprocessor. get a file.as and creat file.am with spread macros */
void Span_Macros(char* fileName)
{
	Macro* macrosTable = NULL;
	Macro* m = NULL;
	FILE* inputf = NULL;
	FILE* outputf = NULL;
	char line[MAX_LINE_LENGTH];
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
	
		c = getc(inputf);
		while (c != EOF)
		{
			line[0] = c;
			fgets(&line[1], MAX_LINE_LENGTH + 1, inputf);
			
			m = Is_Macro_Call(macrosTable, line);
		
			if (m != NULL)
			{
				fprintf(outputf, "%s", m -> macroText);
			}
			
			else if (Is_Macro_Def(line, macroName) == 1)
			{
				strcpy(macroText, "");
				Get_Macro_text(macroText, inputf);
				macrosTable = insert_macro(macrosTable, macroName, macroText);
			}
			
			else
			{
				fprintf(outputf, "%s", line);
			}

			c = getc(inputf);
		}
		
		destroy_macro_table(macrosTable);
		fclose(inputf);
		fclose(outputf);
	}


}
