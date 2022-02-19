#include"../helpers/helpers.h"

#define MAX_DATA_LENGTH (5) /* a word can hold integers between -2047 to 2048 (16 bits) so the length is 4 and one more for '-' */

int get_first_value(char* line);

int quot_marks_counter(char* line);

int conv_method(char* line, char* method, bool is_label_first);

int conv_command(char* line,int command_kind, bool is_label_first);
