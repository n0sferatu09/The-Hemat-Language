#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "../hashtable/hashtable.h"
#include "../vector/vector.h"
#include "lexemes/lexemes.h"
#include "tokens/tokens.h"
#include "lexer.h"

Token* get_keyword_token(FILE *file, Vector* vector, HashTable *keywords, int first_letter) {
    if (first_letter == EOF) return NULL;

    vector_clear(vector);

    Token *token = (Token *)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }

    vector_append(vector, (char)first_letter);
    int current = fgetc(file);
    while ((isalnum(current) || current == '_') && current != EOF) {
        vector_append(vector, (char)current);
        current = fgetc(file);
    }
    ungetc(current, file);

    char *lexeme = get_string(vector);
    int token_type = get(keywords, lexeme);

    if (token_type != -1) {
        token->type = token_type;
    } else {
        token->type = ID;
    }
    token->string_value = strdup(lexeme);

    return token;
}

Token* get_string_token(FILE *file, Vector *vector) {
    vector_clear(vector);

    Token *token = (Token *)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }

    int current = fgetc(file);
    while (current != '\"' && current != EOF) {
        vector_append(vector, (char)current);
        current = fgetc(file);
    }

    if (current == EOF) {
        fprintf(stderr, "ERROR: ' \" 'was expected at the end of the line");
        free(token);
        return NULL;
    }

    char *lexeme = get_string(vector);
    token->type = STRING;
    token->string_value = strdup(lexeme);
    return token;
}

Token* get_number_token(FILE *file, int first_letter) {
    if (first_letter == EOF) return NULL;

    Token *token = (Token *)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }

    long long int buffer = 0;
    buffer = buffer * 10 + (first_letter - '0');

    int current = fgetc(file);
    while (isdigit(current) && current != EOF) {
        buffer = buffer * 10 + (current - '0');
        current = fgetc(file);
    }
    ungetc(current, file);

    token->type = NUMBER;
    token->int_value = buffer;
    return token;
}

Token* get_operator_token(FILE *file, HashTable *operators, int first_symbol) {
    if (first_symbol == EOF) return NULL;

    Token *token = (Token*)malloc(sizeof(Token));
    if (!token) {
        fprintf(stderr, "Memory allocation failed!\n");
        return NULL;
    }


    char buffer[3] = {0};
    buffer[0] = (char)first_symbol;

    int second_symbol = fgetc(file);
    if (second_symbol != EOF) {
        buffer[1] = (char)second_symbol;

        int token_type = get(operators, buffer);
        if (token_type != -1) {
            token->type = token_type;
            token->string_value = strdup(buffer);
            return token;
        }

        ungetc(second_symbol, file);
    }

    buffer[1] = '\0';
    int token_type = get(operators, buffer);
    if (token_type != -1) {
        token->type = token_type;
        token->string_value = strdup(buffer);
        return token;
    }

    free(token);
    return NULL;
}

TokenList *lexer(FILE *file) {
    TokenList *token_list = create_token_list();
    Vector *vector = create_vector();
    HashTable *keywords = init_keywords_table();
    HashTable *operators = init_operators_table();

    int current = fgetc(file);
    while (current != EOF) {
        if (isspace(current)) {
            current = fgetc(file);
            continue;
        }

        if (current == '/') {
            int next = fgetc(file);
            if (next == '/') {
                while ((current = fgetc(file)) != '\n' && current != EOF);
                current = fgetc(file);
                continue;
            } else {
                ungetc(next, file);
            }

        } else if (isalpha(current)) {
            Token *token = get_keyword_token(file, vector, keywords, current);
            if (token) {
                    add_token(token_list, token);
            }
            current = fgetc(file);
            continue;

        } else if (current == '\"') {
            Token *token = get_string_token(file, vector);
            if (token) {
                add_token(token_list, token);
            }
            current = fgetc(file);
            continue;

        } else if (isdigit(current)) {
            Token *token = get_number_token(file, current);
            if (token) {
                add_token(token_list, token);
            }
            current = fgetc(file);
            continue;

        } else if (ispunct(current)) {
            Token *token = get_operator_token(file, operators, current);
            if (token) {
                add_token(token_list, token);
            }
            current = fgetc(file);
            continue;
        }

        fprintf(stderr, "Unknown characters: %c\n", current);
        current = fgetc(file);
    }

    free_vector(vector);
    free_table(keywords);
    free_table(operators);

    return token_list;
}