#include <stdlib.h>
#include <stdio.h>
#include "macros_table.h"
#include "helpers/helpers.h"

void Span_Macros(char* fileName);

int Is_Macro_Def(char* line, char* name);

void Get_Macro_text(char* macroText, FILE* fp1);

Macro* Is_Macro_Call(Macro* m, char* line);
