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
    symbol_table->buckets = NULL;

    return symbol_table;
}

unsigned int hash(const char *str, const int table_size) {
    unsigned long hash = 5381;
    while (*str) hash = ((hash << 5) + hash) + *str++;
    return hash / table_size;
}

void symbol_table_insert(SymbolTable *symbol_table, const char *name, DataType type) {
    if (!symbol_table || !name) return;

    unsigned int index = hash(name, TABLE_SIZE);

    Symbol *current = (Symbol *)malloc(sizeof(Symbol));
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
    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));

}