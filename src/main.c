#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable/hashtable.h"
#include "vector/vector.h"
#include "lexer/lexer.h"
#include "parser/parser.h"

int main(int argc, char *argv[]) {
#if 0
    if (argc < 2) {
        fprintf(stderr, "Usage: hematc <filename.hm>");
        return 1;
    }
#endif

    FILE *file = fopen("../test.hm", "r");

    if (!file) {
        perror("fopen");
        return 1;
    }

    parser(file);

    fclose(file);
    return 0;
}