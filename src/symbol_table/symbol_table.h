#ifndef HEMATC_SYMBOL_TABLE_H
#define HEMATC_SYMBOL_TABLE_H

#include <stdbool.h>

#define TABLE_SIZE 101

typedef enum {
    TYPE_INTEGER,
    TYPE_STRING,
} DataType;

typedef struct Symbol {
    char *name;
    DataType type;
    struct Symbol *next;
} Symbol;

typedef struct {
    Symbol **buckets;
    int size;
} SymbolTable;

SymbolTable* create_symbol_table(void);
void symbol_table_insert(SymbolTable *symbol_table, const char *name, DataType type);
Symbol* lookup_symbol(SymbolTable *symbol_table, const char *name);
void free_symbol_table(SymbolTable *symbol_table);

#endif //HEMATC_SYMBOL_TABLE_H
