#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"

TokenList* create_token_list(void) {
    TokenList *token_list = (TokenList *)malloc(sizeof(TokenList));
    if (!token_list) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
    }
    token_list->capacity = 8;
    token_list->count = 0;
    token_list->tokens = (Token **)malloc(sizeof(Token *) * token_list->capacity);
    if (!token_list->tokens) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(token_list);
        exit(-1);
    }

    return token_list;
}

static void increase_size(TokenList *token_list) {
    token_list->capacity *= 2;
    Token **new_tokens = (Token **)realloc(token_list->tokens, sizeof(Token *) * token_list->capacity);
    if (!new_tokens) {
        fprintf(stderr, "Memory reallocation failed!\n");
        exit(-1);
    }
    token_list->tokens = new_tokens;
}

void add_token(TokenList *token_list, Token *token) {
    if (!token_list || !token) {
        fprintf(stderr, "add_token: invalid arguments\n");
        exit(-1);
    }

    if (token_list->count >= token_list->capacity) {
        increase_size(token_list);
    }

    token_list->tokens[token_list->count++] = token;
}

Token* get_token(TokenList *token_list, int index) {
    if (!token_list || index > token_list->count) {
        return NULL;
    }

    return token_list->tokens[index];
}

int get_count(TokenList *token_list) {
    if (!token_list) return 0;
    return token_list->count;
}

void free_token_list(TokenList *token_list) {
    if (!token_list) return;

    for (int i = 0; i < token_list->count; ++i) {
        if (token_list->tokens[i]) {
            if (token_list->tokens[i]->string_value) {
                free(token_list->tokens[i]->string_value);
            }
            free(token_list->tokens[i]);
        }
    }
    free(token_list->tokens);
    free(token_list);
}