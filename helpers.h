#include <stdbool.h>
#include <stdio.h>

#define BASE_ADRESS     (100)
#define MAX_LABEL_LENGTH (31)

bool is_saved_word(char* value);

int is_command(char* value);

bool is_instruction(char* value);

int remove_unused_whitespaces(char* line, char* result);

/* reg number if so, else -1 */
int get_reg_number(char* value);

char* trim(char *str);

int is_label_def(char* line, char* label_name);

bool is_comment(char* line);

bool is_empty(char* line);

