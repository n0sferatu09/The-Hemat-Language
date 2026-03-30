#ifndef HEMATC_LEXER_H
#define HEMATC_LEXER_H

void lexer(FILE *file) {
    int current = fgetc(file);

    while (current != EOF) {

        current = fgetc(file);
    }
}

#endif //HEMATC_LEXER_H
