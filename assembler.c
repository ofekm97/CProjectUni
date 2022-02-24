#include "preprocessor/preprocessor.h"
#include "symbols/first_move.h"
#include "symbols/second_move.h"

int main(int argc, char* argv[])
{	
	Symbol* symbol_table = NULL;

	span_macros(argv[1]);
	if (first_move(strcat(cut_as(argv[1]), ".am"), symbol_table))
	{
		print_symbols(symbol_table);/* כאן אמור להיות הטבלה המעודכנת אחרי המעבר הראשון */
		second_move(argv[1], symbol_table);
		return 1;
	}

	return 0;
}
