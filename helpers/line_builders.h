#include <stdbool.h>


#define ALL_OPCODE_BITS_ON  (65535)
#define A_LOCATION          (18)
#define R_LOCATION          (17)
#define E_LOCATION          (16)
#define FUNC_LOCATION       (12)
#define ORIG_REG_LOCATION   (8)
#define ORIG_ADD_LOCATION   (6)
#define DEST_REG_LOCATION   (2)
#define DEST_ADD_LOCATION   (0)

#define MAX_WORD_COUNT      (6)
#define ADDRESS_STEPS       (16)

#define HEX_STRING_LENGTH   (15)
#define HEX_STRING_SEP      '-'
#define LINE_BITS_COUNT     (20)
#define GROUP_SIZE          (4)
#define GORUPS_COUNT        (LINE_BITS_COUNT/GROUP_SIZE)

#define HEX_1111            (0xf)
#define HEX_11              (3)


/* Word structure
*
*   In case of first word should be using opcode
*   second word the other values
*   third data (data of additional words) is in opcode (to save space)
*/
typedef struct Word
{
    bool A;
    bool R;
    bool E;
    short func;
    short orig_reg;
    short orig_addressing;
    short dest_reg;
    short dest_addressing;
    int opcode;
    struct Word* next;
} Word;


typedef struct WordArray
{
    Word* words;
    int size;
} WordArray;

int convert_words_to_ints(Word words[MAX_WORD_COUNT], int return_values[MAX_WORD_COUNT], int size);

int convert_int_to_hex_line(int line_value, char hex_value[HEX_STRING_LENGTH]);

int get_base_and_offset(int address, int* base, int* offset);
