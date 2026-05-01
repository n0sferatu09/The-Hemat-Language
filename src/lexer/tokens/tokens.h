#ifndef HEMATC_TOKENS_H
#define HEMATC_TOKENS_H

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_ERROR,

    // keywords
    LET, IF, THEN, ENDIF, LOOP, ENDLOOP, BREAK, PRINT,

    // user tokens
    ID, STRING, NUMBER,

    // operators
    ADD, SUB, MULT, DIV, ASSIGN,

    // logical
    GT, LT, EQ, NEQ,

    // separators
    LPAREN, RPAREN, SEMICOLON
} TokenType;

typedef struct {
    TokenType type;
    long long int int_value;
    char *string_value;
} Token;

typedef struct {
    Token **tokens;
    int capacity;
    int count;
} TokenList;

TokenList* create_token_list(void);
Token* get_token(TokenList *token_list, int index);
void add_token(TokenList *token_list, Token *token);
void free_token_list(TokenList *token_list);
int get_count(TokenList *token_list);

#endif //HEMATC_TOKENS_H
