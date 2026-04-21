#ifndef HEMATC_AST_H
#define HEMATC_AST_H

#include "../lexer/tokens/tokens.h"

typedef enum {
    PROGRAM,
    LET_STATEMENT,
    PRINT_STATEMENT,
    IF_STATEMENT,
    BINARY_EXPRESSION,
    NUMBER_LITERAL,
    STRING_LITERAL,
    IDENTIFIER,
} NodeType;

typedef struct ASTNode{
    NodeType type;
    long long int int_value;
    char *string_value;

    struct ASTNode *next;
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

ASTNode* create_node(NodeType type);
void print_ast(ASTNode *node);
void free_ast(ASTNode *node);

#endif //HEMATC_AST_H
