#include "preprocessor/preprocessor.h"
#include "symbols/first_move.h"
#include "symbols/second_move.h"

int main(int argc, char* argv[])
{	
	Symbol* symbol_table = NULL;

	span_macros(argv[1]);
	first_move(strcat(cut_as(argv[1]), ".am"));

	return 0;
}
