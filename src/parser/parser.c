#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lexer/tokens/tokens.h"
#include "../lexer/lexer.h"
#include "../ast/ast.h"

static ASTNode* parse_expression(TokenList *token_list, int *pos);
static ASTNode* parse_print_statement(TokenList *token_list, int *pos);
static ASTNode* parse_let_statement(TokenList *token_list, int *pos);
static ASTNode* parse_if_statement(TokenList *token_list, int *pos);
static ASTNode* parse_loop_statements(TokenList *token_list, int *pos);
static ASTNode* parse_statements(TokenList *token_list, int *pos);

static Token* peek(TokenList *token_list, const int pos) {
    return get_token(token_list, pos);
}

static bool match(TokenList *token_list, const int pos, const TokenType token_type) {
    Token *token = peek(token_list, pos);
    if (!token) return false;
    return token->type == token_type;
}

static Token* consume(TokenList *token_list, int *pos, const TokenType token_type) {
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

    const Token *token = consume(token_list, pos, ID);

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

static ASTNode* parse_if_statement(TokenList *token_list, int *pos) {
    consume(token_list, pos, IF);

    ASTNode *condition = parse_expression(token_list, pos);
    if (!condition) return NULL;

    consume(token_list, pos, THEN);

    ASTNode *body = parse_statements(token_list, pos);
    if (!body) return NULL;

    consume(token_list, pos, ENDIF);
    consume(token_list, pos, SEMICOLON);
    ASTNode *node = create_node(IF_STATEMENT);
    node->left = condition;
    node->right = body;

    return node;
}

static ASTNode* parse_loop_statements(TokenList *token_list, int *pos) {
    consume(token_list, pos, LOOP);

    ASTNode *body = parse_statements(token_list, pos);
    if (!body) return NULL;

    consume(token_list, pos, ENDLOOP);
    consume(token_list, pos, SEMICOLON);
    ASTNode *node = create_node(LOOP_STATEMENT);
    node->right = body;

    return node;
}

static ASTNode* parse_statements(TokenList *token_list, int *pos) {
    ASTNode *first = NULL;
    ASTNode *last = NULL;

    while (*pos < token_list->count) {
        Token *token = peek(token_list, *pos);
        if (!token) {
            break;
        }

        if (token->type == ENDIF || token->type == ENDLOOP) {
            break;
        }

        ASTNode *stmt = NULL;

        switch (token->type) {
            case LET:
                stmt = parse_let_statement(token_list, pos);
                break;
            case PRINT:
                stmt = parse_print_statement(token_list, pos);
                break;
            case IF:
                stmt = parse_if_statement(token_list, pos);
                break;
            case LOOP:
                stmt = parse_loop_statements(token_list, pos);
                break;
            default:
                fprintf(stderr, "Syntax error: unexpected token %d\n", token->type);
                return NULL;
        }
        if (!stmt) return NULL;

        if (!first) {
            first = stmt;
            last = stmt;
        } else {
            last->next = stmt;
            last = stmt;
        }
    }

    return first;
}

void parser(FILE *file) {
    TokenList *token_list = lexer(file);
    int pos = 0;

    ASTNode *program = create_node(PROGRAM);
    ASTNode *last_statement = NULL;

    while (pos < token_list->count) {
        const Token *current_token = peek(token_list, pos);

        ASTNode *stmt = NULL;

        if (current_token->type == LET) {
            stmt = parse_let_statement(token_list, &pos);
        } else if (current_token->type == PRINT) {
            stmt = parse_print_statement(token_list, &pos);
        } else if (current_token->type == IF) {
            stmt = parse_if_statement(token_list, &pos);
        } else if (current_token->type == LOOP) {
            stmt = parse_loop_statements(token_list, &pos);
        } else {
            fprintf(stderr, "Unexpected token at position %d\n", pos);
            break;
        }

        if (!stmt) {
            fprintf(stderr, "Failed to parse statement\n");
            break;
        }

        if (!program->right) {
            program->right = stmt;
            last_statement = stmt;
        } else {
            last_statement->next = stmt;
            last_statement = stmt;
        }
    }
    print_ast(program);
    free_ast(program);

    free_token_list(token_list);
}