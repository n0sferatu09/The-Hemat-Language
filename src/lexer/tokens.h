#ifndef HEMATC_TOKENS_H
#define HEMATC_TOKENS_H

typedef enum {
    TOKEN_EOF = 0,
    TOKEN_ERROR,

    // keywords
    LET, IF, THEN, LOOP, ENDLOOP, PRINT,

    // user tokens
    ID, STRING, NUMBER,

    // operators
    ADD, SUB, MULT, DIV, ASSIGN,

    // logical
    GT, LT, EQ, NEQ,

    // separators
    LPAREN, RPAREN, SEMICOLON


} TokenType;

#endif //HEMATC_TOKENS_H
