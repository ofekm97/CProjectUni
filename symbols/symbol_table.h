#ifndef LINE_BUILDER
	#define LINE_BUILDER
	#include "../helpers/line_builders.h"
#endif

#define MAX_LABEL_LENGTH (31)
#define DONT_KNOW (0)
#define CODE (1)
#define DATA (2)
#define EXTERNAL (3)

typedef struct Symbol
{

	char label_name[MAX_LABEL_LENGTH];

	int value;

	int base_add;

	int offset;

	short attribute; /* CODE, DATA, EXTERNAL or DONT_KNOW */

	bool entry;

	struct Symbol *next;

} Symbol;

Symbol *new_symbol(char *label_name, int value, short attribute, bool entry);

Symbol *insert_symbol(Symbol *symbol_table, char *name, int value, short attribute, bool entry);

void destroy_symbol_table(Symbol *symbol_table);

Symbol *fix_symbol_table(Symbol *symbol_table, int ic);

void print_symbols(Symbol *symbol_table);

Symbol *search_symbol(Symbol *symbol_table, char *name);
