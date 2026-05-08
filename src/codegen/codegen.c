#include <stdio.h>
#include <stdlib.h>

#include "../lexer/tokens/tokens.h"
#include "../parser/parser.h"
#include "../ast/ast.h"
#include "codegen.h"

void codegen(ASTNode *node, FILE *output, int indent) {
    if (!node) return;

    switch (node->type) {
        case PROGRAM:
            fprintf(output, "#include <stdio.h>\n\n");
            fprintf(output, "int main() {\n");
            codegen(node->right, output, indent + 1);
            fprintf(output, "    return 0;\n");
            fprintf(output, "}\n");
            break;

        case NUMBER_LITERAL:
            fprintf(output, "%lld", node->int_value);
            return;

        case STRING_LITERAL:
            fprintf(output, "\"%s\"", node->string_value);
            return;

        case IDENTIFIER:
            fprintf(output, "%s", node->string_value);
            return;

        case BINARY_EXPRESSION: {
            fprintf(output, "(");
            codegen(node->left, output, indent);
            switch (node->int_value) {
                case ADD: fprintf(output, " + "); break;
                case SUB: fprintf(output, " - "); break;
                case MULT: fprintf(output, " * "); break;
                case DIV: fprintf(output, " / "); break;
                case GT: fprintf(output, " > "); break;
                case LT: fprintf(output, " < "); break;
                case EQ: fprintf(output, " == "); break;
                case NEQ: fprintf(output, " != "); break;
                default: fprintf(output, " ? "); break;
            }
            codegen(node->right, output, indent);
            fprintf(output, ")");
            return;
        }

        case LET_STATEMENT:
            if (node->data_type == TYPE_INTEGER) {
                fprintf(output, "%*slong long int %s = ", indent * 4, "", node->string_value);
                codegen(node->right, output, indent);
                fprintf(output, ";\n");
            }

            if (node->data_type == TYPE_STRING) {
                fprintf(output, "%*sconst char *%s = ", indent * 4, "", node->string_value);
                codegen(node->right, output, indent);
                fprintf(output, ";\n");
            }

            codegen(node->next, output, indent);
            return;

        case ASSIGNMENT_STATEMENT:
            fprintf(output, "%*s%s = ", indent * 4, "", node->string_value);
            codegen(node->right, output, indent);
            fprintf(output, ";\n");
            codegen(node->next, output, indent);
            return;

        case IF_STATEMENT:
            fprintf(output, "%*sif (", indent * 4, "");
            codegen(node->left, output, indent);
            fprintf(output, ") {\n");
            codegen(node->right, output, indent + 1);
            fprintf(output, "%*s}\n", indent * 4, "");
            codegen(node->next, output, indent);
            return;

        case LOOP_STATEMENT:
            fprintf(output, "%*sfor (;;) {\n", indent * 4, "");
            codegen(node->right, output, indent+1);
            fprintf(output, "%*s}\n", indent * 4, "");
            codegen(node->next, output, indent);
            return;

        case PRINT_STATEMENT:
            if (node->data_type == TYPE_INTEGER) {
                fprintf(output, "%*sprintf(\"%%lld\", (long long int)", indent * 4, "");
                codegen(node->right, output, indent);
                fprintf(output, ");\n");
            }

            if (node->data_type == TYPE_STRING) {
                fprintf(output, "%*sprintf(\"%%s\", ", indent * 4, "");
                codegen(node->right, output, indent);
                fprintf(output, ");\n");
            }
            codegen(node->next, output, indent);
            return;

        case BREAK_STATEMENT:
            fprintf(output, "%*sbreak;\n", indent * 4, "");
            codegen(node->next, output, indent);
            return;


        default:
            fprintf(stderr, "Code generation error\n");
    }
}