#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#ifndef METHODS
	#define METHODS
	#include "../methods/methods.h"
#endif

#define BASE_ADDRESS     (100)
#define MAX_LINE_LENGTH (80)
#define MAX_LABEL_LENGTH (31)
#define MAX_MACRO_NAME_LENGTH (31)

bool check_lines_size(FILE* file, int max);

void clean_whitespace_chars(char* line, char* cleanLine);

int is_command(char* line, char* ext_label_name);

int remove_unused_whitespaces(char* line, char* result);

/* reg number if so, else -1 */
int get_reg_number(char* value);

char* trim(char *str);

int is_label_def(char* line, char* label_name);

bool is_comment(char* line);

bool is_empty(char* line);

char* cut_as(char* str);

void get_method_name(char* line, bool is_label_first, char* method_name);

bool is_legal_label(Method* command_list, char* label);

int commas_counter(char* line);

bool split_operands(char* line, bool is_label_first, char* orig_op, char* dest_op);
