#include "macros_table.h"

/* create new macro */
macro* New_Macro(char* name, char* text)
{
	macro* tmp = NULL;
	tmp = (macro*) malloc(sizeof(macro));
	if (tmp != NULL)
	{
		strcpy(tmp -> macroName, name);
		strcpy(tmp -> macroText, text);
		tmp -> nextMacro = NULL;
	}

	return tmp;
}

/* insert macro to the macros table */
macro* Insert_Macro(macro* m, char* name, char* text)
{
	if(m == NULL)
	{
		return New_Macro(name, text);
	}

	if(m -> nextMacro == NULL)
	{
		m -> nextMacro = New_Macro(name, text);
		return m;
	}

	Insert_Macro(m -> nextMacro, name, text);
	return m;
}

/* return the macro with the name "str" or null if macro "str" is not exist in the macros table */
macro* Is_Macro_Name(macro* m, char* str)
{
	if (m == NULL)
	{
		return NULL;
	}
	
	if (strcmp(m -> macroName, str) == 0)
	{
		return m;
	}

	else
	{
		return Is_Macro_Name(m -> nextMacro, str);
	}
}

/* delete macros table */
void Destroy_Macro_Table(macro* m)
{
	if (m == NULL)
	{
		return;
	}

	Destroy_Macro_Table(m -> nextMacro);
	free(m);
}

