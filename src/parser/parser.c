#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lexer/tokens/tokens.h"
#include "../lexer/lexer.h"
#include "ast/ast.h"

static Token* peek(TokenList *token_list, int pos) {
    return get_token(token_list, pos);
}

static bool match(TokenList *token_list, int pos, TokenType token_type) {
    Token *token = peek(token_list, pos);
    if (!token) return false;
    return token->type == token_type;
}

static Token* consume(TokenList *token_list, int *pos, TokenType token_type) {
    if (!match(token_list, *pos, token_type)) {
        fprintf(stderr, "Syntax error: expected token %d", token_type);
        exit(-1);
    }
    Token *token = peek(token_list, *pos);
    (*pos)++;
    return token;
}

static ASTNode* parse_expression(TokenList *token_list, int *pos) {
    Token *token = peek(token_list, *pos);
    if (!token) return NULL;

    if (token->type == NUMBER) {
        consume(token_list, pos, NUMBER);

        ASTNode *node = create_node(NUMBER_LITERAL);
        node->int_value = token->int_value;
        return node;
    }

    if (token->type == STRING) {
        consume(token_list, pos, STRING);

        ASTNode *node = create_node(STRING_LITERAL);
        node->string_value = strdup(token->string_value);
        return node;
    }

    if (token->type == ID) {
        consume(token_list, pos, ID);

        ASTNode *node = create_node(IDENTIFIER);
        node->string_value = strdup(token->string_value);
        return node;
    }

    fprintf(stderr, "Expected number or identifier, got %d\n", token->type);
    return NULL;
}

static ASTNode* parse_let_statement(TokenList *token_list, int *pos) {
    consume(token_list, pos, LET);

    Token *token = consume(token_list, pos, ID);

    consume(token_list, pos, ASSIGN);

    ASTNode *expr = parse_expression(token_list, pos);
    if (!expr) return NULL;

    consume(token_list, pos, SEMICOLON);

    ASTNode *node = create_node(LET_STATEMENT);
    node->string_value = strdup(token->string_value);
    node->right = expr;
    return node;
}

static ASTNode* parse_print_statement(TokenList *token_list, int *pos) {
    consume(token_list, pos, PRINT);

    ASTNode *expr = parse_expression(token_list, pos);
    if (!expr) return NULL;

    consume(token_list, pos, SEMICOLON);
    ASTNode *node = create_node(PRINT_STATEMENT);
    node->right = expr;
    return node;
}

void parser(FILE *file) {
    TokenList *token_list = lexer(file);
    int pos = 0;

    parse_let_statement(token_list, &pos);
    parse_print_statement(token_list, &pos);
    parse_print_statement(token_list, &pos);
    printf("Hello, World!\n");
}