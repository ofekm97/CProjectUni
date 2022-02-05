#include "macros_table.h"

/* create new Macro */
Macro* new_macro(char* name, char* text)
{
	Macro* tmp = NULL;
	tmp = (Macro*) malloc(sizeof(Macro));
	if (tmp != NULL)
	{
		strcpy(tmp -> macroName, name);
		strcpy(tmp -> macroText, text);
		tmp -> nextMacro = NULL;
	}

	return tmp;
}

/* insert Macro to the macros table */
Macro* insert_macro(Macro* m, char* name, char* text)
{
	if(m == NULL)
	{
		return new_macro(name, text);
	}

	if(m -> nextMacro == NULL)
	{
		m -> nextMacro = new_macro(name, text);
		return m;
	}

	insert_macro(m -> nextMacro, name, text);
	return m;
}

/* return the Macro with the name "str" or null if Macro "str" is not exist in the macros table */
Macro* is_macro_name(Macro* m, char* str)
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
		return is_macro_name(m -> nextMacro, str);
	}
}

/* delete macros table */
void destroy_macro_table(Macro* m)
{
	if (m == NULL)
	{
		return;
	}

	destroy_macro_table(m -> nextMacro);
	free(m);
}

