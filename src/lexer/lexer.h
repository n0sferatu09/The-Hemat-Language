#ifndef HEMATC_LEXER_H
#define HEMATC_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

static inline Token *get_keyword_token(FILE *file, int current) {
    Token *token = (Token *)malloc(sizeof(Token));
    char *buffer = {};
}

static inline void lexer(FILE *file) {
    int current = fgetc(file);

    while (current != EOF) {
        if (isalpha(current)) {
            Token *token =  get_keyword_token(file, current);
        }

        current = fgetc(file);
    }
}

#endif //HEMATC_LEXER_H
