#include "preprocessor.h"
#include "first_move.h"

int main(int argc, char* argv[])
{	
	Span_Macros(argv[1]);
	first_move(strcat(cut_as(argv[1]), ".am"));
	return 0;
}
