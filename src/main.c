#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table/symbol_table.h"
#include "semantic/semantic.h"
#include "codegen/codegen.h"
#include "parser/parser.h"
#include "ast/ast.h"

int main(int argc, char *argv[]) {
#if 0
    if (argc < 2) {
        fprintf(stderr, "Usage: hmc <filename.hm>");
        return 1;
    }
#endif

    FILE *file = fopen("../syntax.hm", "r");
    if (!file) {
        perror("fopen");
        return 1;
    }


    FILE *output = fopen("../test.c", "w");
    if (!output) {
        perror("fopen");
        return 1;
    }

    ASTNode *ast = parser(file);

    SymbolTable *symbol_table = create_symbol_table();

    bool ok = semantic_analyze(ast, symbol_table);

    free_symbol_table(symbol_table);

    codegen(ast, output, 0);

    fclose(file);
    fclose(output);
    return 0;
}
