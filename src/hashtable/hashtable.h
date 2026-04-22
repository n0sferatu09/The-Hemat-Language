#ifndef HEMATC_HASHTABLE_H
#define HEMATC_HASHTABLE_H

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct HashTable {
    Entry **buckets;
    int size;
} HashTable;

HashTable* create_table(int size);
void insert(HashTable *hashtable, const char *key, int value);
int get_value(HashTable *hashtable, const char *key);
void free_table(HashTable *hashtable);

#endif //HEMATC_HASHTABLE_H
