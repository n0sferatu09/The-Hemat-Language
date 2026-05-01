#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"

HashTable* create_table(int size) {
    HashTable *hashtable = (HashTable *)malloc(sizeof(HashTable));
    if (!hashtable) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
    }

    hashtable->size = size;
    hashtable->buckets = calloc(size, sizeof(Entry*));
    if (!hashtable->buckets) {
        free(hashtable);
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
    }

    return hashtable;
}

unsigned int hash(const char *str, const int table_size) {
    unsigned long hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *str++;
    return hash % table_size;
}

void insert(HashTable *hashtable, const char *key, int value) {
    unsigned int index = hash(key, hashtable->size);
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = hashtable->buckets[index];
    hashtable->buckets[index] = new_entry;
}

int get_value(HashTable *hashtable, const char *key) {
    if (!hashtable) {
        fprintf(stderr, "Hashtable is not exists!\n");
        exit(-1);
    }

    unsigned int index = hash(key, hashtable->size);
    Entry *entry = hashtable->buckets[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return -1;
}

void free_table(HashTable *hashtable) {
    for (int i = 0; i < hashtable->size; ++i) {
        Entry *entry = hashtable->buckets[i];
        while (entry) {
            Entry *next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(hashtable->buckets);
    free(hashtable);
}