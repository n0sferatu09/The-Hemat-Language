#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "codegen/codegen.h"
#include "ast/ast.h"
#include "parser/parser.h"

int main(int argc, char *argv[]) {
#if 0
    if (argc < 2) {
        fprintf(stderr, "Usage: hematc <filename.hm>");
        return 1;
    }
#endif

    FILE *file = fopen("../test.hm", "r");
    if (!file) {
        perror("fopen");
        return 1;
    }


    FILE *output = fopen("../test.c", "w");
    if (!output) {
        perror("fopen");
        return 1;
    }

    ASTNode *main_node = parser(file);
    codegen(main_node, output, 1);

    fclose(file);
    fclose(output);
    return 0;
}