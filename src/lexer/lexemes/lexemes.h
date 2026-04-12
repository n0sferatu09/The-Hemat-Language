#ifndef HEMATC_LEXEMES_H
#define HEMATC_LEXEMES_H

#include "../../hashtable/hashtable.h"

#define TABLE_SIZE 64

HashTable *init_keywords_table(void);
HashTable *init_operators_table(void);

#endif //HEMATC_LEXEMES_H
