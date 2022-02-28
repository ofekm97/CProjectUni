#ifndef SYMBOL
	#include "symbol_table.h"
#endif

#define SECOND_MOVE

bool write_to_entries_file(Symbol* symbol, char* file_name, bool is_first_entry);

bool second_move(FILE* inputf, Symbol* symbol_table, char* file_name);
