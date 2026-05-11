#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "command_parser.h"

static void print_usage(void) {
    fprintf(stderr, "Usage: hmc <file.hm> [--compile] [--cc=<compiler>]\n");
    fprintf(stderr, "Compilers: gcc, g++, clang, clang++\n");
}

static char* strdup_custom(const char *s) {
    if (!s) return NULL;
    char *d = malloc(strlen(s) + 1);
    if (d) strcpy(d, s);
    return d;
}

static Compiler parse_compiler(const char *str) {
    if (strcmp(str, "gcc") == 0) return CC_GCC;
    if (strcmp(str, "g++") == 0) return CC_GPP;
    if (strcmp(str, "clang") == 0) return CC_CLANG;
    if (strcmp(str, "clang++") == 0) return CC_CLANGPP;
    return CC_NONE;
}

Flags* parse_flags(int argc, char **argv) {
    if (argc < 2) {
        print_usage();
        return NULL;
    }

    Flags *flags = calloc(1, sizeof(Flags));
    if (!flags) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    flags->compile_flag = false;
    flags->cc = CC_NONE;
    flags->input_filename = NULL;

    bool input_found = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--compile") == 0) {
            flags->compile_flag = true;
        }
        else if (strncmp(argv[i], "--cc=", 5) == 0) {
            const char *comp = argv[i] + 5;
            flags->cc = parse_compiler(comp);
            if (flags->cc == CC_NONE) {
                fprintf(stderr, "Error: unknown compiler '%s'\n", comp);
                print_usage();
                free_flags(flags);
                return NULL;
            }
        }
        else if (argv[i][0] == '-') {
            fprintf(stderr, "Error: unknown option '%s'\n", argv[i]);
            print_usage();
            free_flags(flags);
            return NULL;
        }
        else {
            if (input_found) {
                fprintf(stderr, "Error: multiple input files specified\n");
                print_usage();
                free_flags(flags);
                return NULL;
            }
            flags->input_filename = strdup_custom(argv[i]);
            if (!flags->input_filename) {
                fprintf(stderr, "Memory allocation failed\n");
                free_flags(flags);
                return NULL;
            }
            input_found = true;
        }
    }

    if (!input_found) {
        fprintf(stderr, "Error: no input file specified\n");
        print_usage();
        free_flags(flags);
        return NULL;
    }

    if (flags->compile_flag && flags->cc == CC_NONE) {
        fprintf(stderr, "Error: --compile requires --cc=<compiler>\n");
        print_usage();
        free_flags(flags);
        return NULL;
    }

    return flags;
}

void free_flags(Flags *flags) {
    if (!flags) return;
    free(flags->input_filename);
    free(flags);
}