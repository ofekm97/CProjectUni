#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BASE_ADDRESS     (100)
#define MAX_LINE_LENGTH (80)
#define MAX_LABEL_LENGTH (31)
#define MAX_MACRO_NAME_LENGTH (31)

#define DATA_COMMAND (1)
#define STRING_COMMAND (2)
#define EXTERN_COMMAND (3)
#define ENTRY_COMMAND (4)

bool check_lines_size(FILE* file, int max);

void clean_whitespace_chars(char* line, char* cleanLine);

int is_command(char* line, char* ext_label_name);

int remove_unused_whitespaces(char* line, char* result);

bool get_reg_number(char* reg_name, int* ret_value);

char* trim(char *str);

int is_label_def(char* line, char* label_name);

bool is_comment(char* line);

bool is_empty(char* line);

char* cut_as(char* str);

void get_method_name(char* line, bool is_label_first, char* method_name);

int commas_counter(char* line);

bool check_operand(char* operand);

bool split_operands(char* line, bool is_label_first, char* orig_op, char* dest_op);

bool get_number_from_string(char* str, signed int* value, bool expect_comma);
