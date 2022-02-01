#include <string.h>
#define MAX_MACRO_NAME_LENGTH 31
#define MAX_LINE_LENGTH 80

typedef struct macro{

	char macroName[MAX_MACRO_NAME_LENGTH];
	
	char macroText[6 * MAX_LINE_LENGTH];

	struct macro* nextMacro;

} macro;

macro* New_Macro(char* name, char* text);

macro* Insert_Macro(macro* m, char* name, char* text);

macro* Is_Macro_Name(macro* m, char* str);

void Destroy_Macro_Table(macro* m);


