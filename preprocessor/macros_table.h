#include "../helpers/helpers.h"

typedef struct Macro{

	char macroName[MAX_MACRO_NAME_LENGTH];
	
	char macroText[6 * MAX_LINE_LENGTH];

	struct Macro* nextMacro;

} Macro;

Macro* new_macro(char* name, char* text);

Macro* insert_macro(Macro* m, char* name, char* text);

Macro* is_macro_name(Macro* m, char* str);

void destroy_macro_table(Macro* m);


