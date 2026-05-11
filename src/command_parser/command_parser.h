#ifndef HMC_COMMAND_PARSE_H
#define HMC_COMMAND_PARSE_H

#include <stdbool.h>

typedef enum {
   CC_GCC,
   CC_GPP,
   CC_CLANG,
   CC_CLANGPP,
   CC_NONE
} Compiler;

typedef struct {
   char *input_filename;
   bool compile_flag;
   Compiler cc;
} Flags;

Flags* parse_flags(int argc, char **argv);
void free_flags(Flags *flags);

#endif