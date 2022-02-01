#include  <stdio.h>

#define CAPACITY 50000 // Size of the Hash Table
 
// Define the Hash Table Item here
typedef struct Ht_item {
    char* key;
    char* value;
} Ht_item;

 
// Define the Linkedlist here
typedef struct LinkedList {
    Ht_item* item; 
    LinkedList* next;
} LinkedList;
 
// Define the Hash Table here
typedef struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
} HashTable;
 

/* Should choose differenct hash function */
unsigned long hash_function(char* str);

Ht_item* create_item(char* key, char* value);

HashTable* create_table(int size);

void free_item(Ht_item* item);

void free_table(HashTable* table);