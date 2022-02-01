#include <stdbool.h>
#include <stdio.h>

#define BASE_ADRESS     (100)

bool is_saved_word(char* value);

bool is_command(char* value);

bool is_instruction(char* value);

int remove_unused_whitespaces(char* line, char* result);

/* reg number if so, else -1 */
int get_reg_number(char* value);

char* trims(char *str);