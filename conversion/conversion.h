#include "../methods/methods.h"
#define MAX_INTEGER (2048)
#define MIN_INTEGER (-2047)

bool get_number_from_data_command(char* str, int* value);

int quot_marks_counter(char* line);

int conv_method(char* line, char* method, bool is_label_first, Method* methods_list, int line_number);

int conv_command(char* line,int command_kind, int line_number);
