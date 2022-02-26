#include "line_builders.h"

int get_ARE(Word *word)
{
    int value = 0;
    if (word->A)
    {
        value |= 1 << A_LOCATION;
    }
    if (word->R)
    {
        value |= 1 << R_LOCATION;
    }
    if (word->E)
    {
        value |= 1 << E_LOCATION;
    }
    return value;
}

int get_second_word(Word *word)
{
    int return_value = 0;
    return_value |= (word->func & HEX_1111) << FUNC_LOCATION;
    return_value |= (word->orig_reg & HEX_1111) << ORIG_REG_LOCATION;
    return_value |= (word->orig_addressing & HEX_11) << ORIG_ADD_LOCATION;
    return_value |= (word->dest_reg & HEX_1111) << DEST_REG_LOCATION;
    return_value |= (word->dest_addressing & HEX_11) << DEST_ADD_LOCATION;
    return return_value;
}

int convert_words_to_ints(Word* words, int return_values[MAX_WORD_COUNT], int size)
{
    Word* current = words;
    int i = 0;
    int current_value = 0;
    for (; i < size; i++, current=current->next);
    {
        current_value = 0;
        current_value |= get_ARE(current);
        /* seccond iteration is the func, dest and orig reg and addressing */
        if (i == 1)
        {
            current_value |= get_second_word(current);
        }
        else
        {
            current_value |= (current->opcode & ALL_OPCODE_BITS_ON);
        }
        return_values[i] = current_value;
    }
    return (int)return_values;
}

int convert_int_to_hex_line(int line_value, char hex_value[HEX_STRING_LENGTH])
{
    int i = GORUPS_COUNT;
    char groups[GORUPS_COUNT] = {'A', 'B', 'C', 'D', 'E'};
    int groups_values[GORUPS_COUNT] = {0, 0, 0, 0, 0};
    for (; 0 < i; i--)
    {
        groups_values[i - 1] = (line_value >> (4 * (GORUPS_COUNT - i))) & HEX_1111;
    }
    i = 0;
    for (; i < GORUPS_COUNT; i++)
    {
        hex_value[3 * i] = groups[i];
        sprintf(hex_value + (3 * i) + 1, "%x", groups_values[i]);
        hex_value[(3 * i) + 2] = HEX_STRING_SEP;
    }
    hex_value[HEX_STRING_LENGTH - 1] = '\0';
    return 1;
}

int get_base_and_offset(int address, int *base, int *offset)
{
    *offset = address % ADDRESS_STEPS;
    *base = address - *offset;
    return 1;
}

bool create_data_word(WordsList* words_list, bool A, bool R, bool E, int data)
{
    Word *new_word = (Word *)malloc(sizeof(Word));
    if (new_word != NULL)
    {
        new_word->is_func_word = false;
        new_word->A = A;
        new_word->R = R;
        new_word->E = E;
        new_word->opcode = data;
        new_word->next = NULL;
    }
    else
    {
        /* should print an error? */
        return false;
    }
    push_to_words_list(words_list, new_word);
    return true;
}

Word *create_func_word(WordsList* words_list, bool A, bool R, bool E, short func, short orig_reg, short orig_addressing, short dest_reg, short dest_addressing)
{
    Word *new_word = (Word *)malloc(sizeof(Word));
    if (new_word != NULL)
    {
        new_word->is_func_word = true;
        new_word->A = A;
        new_word->R = R;
        new_word->E = E;
        new_word->func = func;
        new_word->orig_reg = orig_reg;
        new_word->orig_addressing = orig_addressing;
        new_word->dest_reg = dest_reg;
        new_word->dest_addressing = dest_addressing;
        new_word->next = NULL;
    }
    else
    {
        /* should print an error? */
        return NULL;
    }
    push_to_words_list(words_list, new_word);
    return new_word;
}

WordsList *init_words_list()
{
    WordsList *words_list = (WordsList *)malloc(sizeof(WordsList));
    if (words_list != NULL)
    {
        words_list->size = 0;
        words_list->words = NULL;
    }
    else
    {
        /* should print an error? */
        return NULL;
    }
    return words_list;
}

void push_to_words_list(WordsList *words_list, Word *new_word)
{
    Word *current = words_list->words;
    if(current == NULL) {
        words_list->words = new_word;
        return;
    }

    while (current->next)
        current = current->next;
    /* now current is pointing the last word in the list */
    current->next = new_word;
    words_list->size++;
}

void destroy_words_list(WordsList *words_list)
{
    Word *next, *current = words_list->words;
    while (current && current->next)
    {
        next = current->next;
        free(current);
        current = next;
    }
    if (words_list != NULL)
        free(words_list);
}

void print_word(Word* current, int index) {
    printf("printing word %d:\n", index);
    printf("A: %d, R: %d, E: %d\n", current->A, current->R, current->E);
    if(current->is_func_word) {
        printf("func: %d, orig_reg: %d, dest_reg: %d\n", current->func, current->orig_reg, current->dest_reg);
        printf("orig_addressing: %d, dest_addressing: %d\n", current->orig_addressing, current->dest_addressing);
    }
    else {
        printf("opcode / data: %d\n", current->opcode);
    }
}

void print_words_list(WordsList *words_list) {
    int i = 1;
    Word *current = words_list->words;
    printf("\n\n***** this is for debug, should not be in final code ***\n");
    while(current) {
        print_word(current, i);
        current = current->next;
        i++;
    }
}