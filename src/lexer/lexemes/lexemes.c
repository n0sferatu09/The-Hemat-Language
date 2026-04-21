#include "../../hashtable/hashtable.h"
#include "../tokens/tokens.h"
#include "lexemes.h"

HashTable* init_keywords_table(void) {
    HashTable *table = create_table(TABLE_SIZE);

    insert(table, "let", LET);
    insert(table, "if", IF);
    insert(table, "then", THEN);
    insert(table, "endif", ENDIF);
    insert(table, "loop", LOOP);
    insert(table, "endloop", ENDLOOP);
    insert(table, "print", PRINT);

    return table;
}

HashTable* init_operators_table(void) {
    HashTable *table = create_table(TABLE_SIZE);

    insert(table, "+", ADD);
    insert(table, "-", SUB);
    insert(table, "*", MULT);
    insert(table, "/", DIV);
    insert(table, "=", ASSIGN);
    insert(table, ">", GT);
    insert(table, "<", LT);
    insert(table, "==", EQ);
    insert(table, "!=", NEQ);
    insert(table, "(", LPAREN);
    insert(table, ")", RPAREN);
    insert(table, ";", SEMICOLON);

    return table;
}