#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command_parser/command_parser.h"
#include "symbol_table/symbol_table.h"
#include "semantic/semantic.h"
#include "codegen/codegen.h"
#include "parser/parser.h"
#include "ast/ast.h"

int main(int argc, char **argv) {
    Flags *flags = parse_flags(argc, argv);
    if (!flags) return 1;

    FILE *file = fopen(flags->input_filename, "r");
    if (!file) {
        perror("fopen");
        free_flags(flags);
        return 1;
    }

    char output_name[256];
    strcpy(output_name, flags->input_filename);
    char *dot = strchr(output_name, '.');
    if (dot) *dot = '\0';
    strcat(output_name, ".c");

    FILE *output = fopen(output_name, "w");
    if (!output) {
        perror("fopen");
        fclose(file);
        free_flags(flags);
        return 1;
    }

    ASTNode *ast = parser(file);
    SymbolTable *symbol_table = create_symbol_table();
    bool ok = semantic_analyze(ast, symbol_table);

    if (ok) {
        codegen(ast, output, 0);
    }

    if (flags->compile_flag && ok) {
        char cmd[512];
        const char *cc =
            flags->cc == CC_GCC ? "gcc" :
            flags->cc == CC_GPP ? "g++" :
            flags->cc == CC_CLANG ? "clang" : "clang++";

        sprintf(cmd, "%s %s -o %s", cc, output_name, flags->input_filename);
        dot = strchr(cmd, '.');
        if (dot) *dot = '\0';

        system(cmd);
    }

    fclose(file);
    fclose(output);
    free_symbol_table(symbol_table);
    free_flags(flags);
    free_ast(ast);
    return 0;
}
