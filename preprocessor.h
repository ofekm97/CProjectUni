#include <stdlib.h>
#include <stdio.h>
#include "macros_table.c"

void Span_Macros(char* fileName);

void Clean_Whitespace_Chars(char* line, char* cleanLine);

int Is_Macro_Def(char* line, char* name);

void Get_Macro_text(char* macroText, FILE* fp1);

macro* Is_Macro_Call(macro* m, char* line);
