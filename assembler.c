#include "preprocessor/preprocessor.h"
#include "symbols/first_move.h"

int main(int argc, char* argv[])
{	
	span_macros(argv[1]);
	first_move(strcat(cut_as(argv[1]), ".am"));
	return 0;
}