#ifndef HEMATC_HEMATC_H
#define HEMATC_HEMATC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer/hash_table.h"
#include "lexer/tokens.h"
#include "lexer/lexer.h"

HashTable *keywords = NULL;

void init_keywords_table() {
    if (keywords) { return; }

    insert(keywords, "let", LET);
    insert(keywords, "if", IF);
    insert(keywords, "then", THEN);
    insert(keywords, "endif", ENDIF);
    insert(keywords, "loop", LOOP);
    insert(keywords, "endloop", ENDLOOP);
    insert(keywords, "print", PRINT);
}



#endif //HEMATC_HEMATC_H
