#include "commands_tester.h"

const char *words_to_test[20] =
    {"mov", "cmp", "add", "sub", "lea", "clr", "not", "inc", "dec", "jmp", "bne", "jsr", "red", "prn", "rts", "stop", "ofek", "yarin", "mov1", "mov "};

void test_commands_list()
{
    int i = 0;
    Command *list = init_commands_list();
    char *word;

    for (; i < 20; i++)
    {
        word = words_to_test[i];
        printf("%s: %d\n", word, command_index(list, word));
    }
    return;
}