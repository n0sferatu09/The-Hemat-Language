#include <stdio.h>
#include <stdlib.h>

#include "lexer/lexer.h"

int main(int argc, char *argv[]) {
#if 0
    if (argc < 2) {
        fprintf(stderr, "Usage: hematc <filename.hm>");
        return 1;
    }
#endif

    FILE *file = fopen("../syntax.hm", "r");

    if (!file) {
        perror("fopen");
        return 1;
    }

    fclose(file);
    return 0;
}