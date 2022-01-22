#include "line_builders.h"
#include "helpers.h"

int getARE(Word *word)
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

int convert_words_to_ints(Word words[MAX_WORD_COUNT], int return_values[MAX_WORD_COUNT])
{
    int i = 0;
    int current_value = 0;
    for (; i < MAX_WORD_COUNT; i++)
    {
        current_value |= getARE(words + i);
        /* seccond iteration is the func, dest and orig reg and addressing */
        if (i == 1)
        {
            current_value |= get_second_word(words + i);
        }
        else 
        {
            current_value |= (words->opcode & ALL_OPCODE_BITS_ON);
        }
        return_values[i] = current_value;
    }
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
    if (address < BASE_ADRESS)
    {
        printf("ERROR - address is smaller then %d", BASE_ADRESS);
        return 0;
    }
    *offset = address % ADDRESS_STEPS;
    *base = address - *offset;
    return 1;
}