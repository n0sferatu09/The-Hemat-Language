#include <stdio.h>
#include <stdlib.h>

#include "../parser/parser.h"
#include "../ast/ast.h"
#include "codegen.h"

void codegen(ASTNode *node, FILE *output, int indent) {
    if (!node) return;

    switch (node->type) {
        case PROGRAM:
            fprintf(output, "#include <stdio.h>\n\n");
            fprintf(output, "int main() {\n");
            codegen(node->right, output, indent);
            fprintf(output, "    return 0;\n");
            fprintf(output, "}\n");
            break;

        case LET_STATEMENT:
            fprintf(output, "%*slong long int %s = %lld;\n", indent * 4, "", node->string_value, node->right->int_value);
            codegen(node->next, output, indent);
            break;

        case PRINT_STATEMENT:
            fprintf(output, "%*sprintf(\"%%lld\\n\", %s);\n", indent * 4, "", node->right->string_value);
            codegen(node->next, output, indent);
            break;

        default:
            fprintf(stderr, "Code generation error\n");
    }
}
