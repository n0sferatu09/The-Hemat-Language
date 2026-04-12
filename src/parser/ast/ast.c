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
}