#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

ASTNode* create_node(NodeType type) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
    }
    node->type = type;
    node->next = NULL;
    node->left = NULL;
    node->right = NULL;
    node->string_value = NULL;
    node->int_value = 0;

    return node;
}

void print_ast(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case PROGRAM:
            printf("PROGRAM\n");
            print_ast(node->right);
            break;

        case LET_STATEMENT:
            printf("LET %s = ", node->string_value);
            print_ast(node->right);
            printf(";\n");
            print_ast(node->next);
            break;

        case PRINT_STATEMENT:
            printf("PRINT ");
            print_ast(node->right);
            printf(";\n");
            print_ast(node->next);
            break;

        case IF_STATEMENT:
            printf("IF ");
            print_ast(node->left);
            printf(" THEN\n");
            print_ast(node->right);
            printf("ENDIF;\n");
            print_ast(node->next);
            break;

        case NUMBER_LITERAL:
            printf("%lld", node->int_value);
            break;

        case STRING_LITERAL:
            printf("%s", node->string_value);
            break;

        case IDENTIFIER:
            printf("%s", node->string_value);
            break;

        case BINARY_EXPRESSION:
            printf("(");
            print_ast(node->left);
            printf(" ? ");
            print_ast(node->right);
            printf(")");
            break;

        default:
            printf("Unknown");
    }
}

void free_ast(ASTNode *node) {
    if (!node) return;

    free_ast(node->left);
    free_ast(node->right);
    free_ast(node->next);

    if (node->string_value) {
        free(node->string_value);
    }

    free(node);
}