#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

SymbolTable* create_symbol_table(void) {
    SymbolTable *symbol_table = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (!symbol_table) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
    }

    symbol_table->size = TABLE_SIZE;
    symbol_table->buckets = calloc(symbol_table->size, sizeof(Symbol*));
    if (!symbol_table->buckets) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
    }

    return symbol_table;
}

static unsigned int hash(const char *str, const int table_size) {
    unsigned long hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *str++;
    return hash % table_size;
}

void symbol_table_insert(SymbolTable *symbol_table, const char *name, DataType type) {
    if (!symbol_table || !name) return;

    unsigned int index = hash(name, symbol_table->size);

    Symbol *current = symbol_table->buckets[index];
    while (current) {
        if (strcmp(current->name, name) == 0) {
            fprintf(stderr, "Error: variable '%s' already declared\n", name);
            return;
        }

        current = current->next;
    }

    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->next = symbol_table->buckets[index];
    symbol_table->buckets[index] = symbol;
}

Symbol* lookup_symbol(SymbolTable *symbol_table, const char *name) {
    if (!symbol_table || !name) return NULL;

    unsigned int index = hash(name, symbol_table->size);
    Symbol *current = symbol_table->buckets[index];

    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void free_symbol_table(SymbolTable *symbol_table) {
    if (!symbol_table) return;

    for (int i = 0; i < symbol_table->size; ++i) {
        Symbol *symbol = symbol_table->buckets[i];
        while (symbol) {
            Symbol *next = symbol->next;
            free(symbol->name);
            free(symbol);
            symbol = next;
        }
    }
    free(symbol_table->buckets);
    free(symbol_table);
}