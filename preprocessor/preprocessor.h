#include <stdlib.h>
#include <stdio.h>
#include "macros_table.h"
#ifndef HELPERS
	#include "../helpers/helpers.h"
#endif

#define PREPROCESSOR

void span_macros(char* fileName);

int is_macro_def(char* line, char* name);

void get_macro_text(char* macroText, FILE* fp1);

Macro* is_macro_call(Macro* m, char* line);
