#include <stdlib.h>
#include <stdio.h>
#include "macros_table.h"
#include "helpers/helpers.h"

void span_macros(char* fileName);

void clean_whitespace_chars(char* line, char* cleanLine);

int is_macro_def(char* line, char* name);

void get_macro_text(char* macroText, FILE* fp1);

Macro* is_macro_call(Macro* m, char* line);
