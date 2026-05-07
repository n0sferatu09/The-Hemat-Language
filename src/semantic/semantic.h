#ifndef HEMATC_SEMANTIC_H
#define HEMATC_SEMANTIC_H

#include <stdio.h>
#include <stdbool.h>

#include "../symbol_table/symbol_table.h"
#include "../ast/ast.h"

bool semantic_analyze(ASTNode *ast, SymbolTable *symbol_table);
void semantic_error(const char *message, ASTNode *node);

#endif //HEMATC_SEMANTIC_H