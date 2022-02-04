#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BASE_ADDRESS     (100)
#define MAX_LINE_LENGTH (80)
#define MAX_LABEL_LENGTH (31)
#define MAX_MACRO_NAME_LENGTH (31)

bool is_saved_word(char* value);

int is_command(char* line, char* ext_label_name);

bool is_instruction(char* value);

int remove_unused_whitespaces(char* line, char* result);

/* reg number if so, else -1 */
int get_reg_number(char* value);

char* trim(char *str);

int is_label_def(char* line, char* label_name);

bool is_comment(char* line);

bool is_empty(char* line);

char* cut_as(char* str);

