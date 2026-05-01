#ifndef HEMATC_CODEGEN_H
#define HEMATC_CODEGEN_H

#include <stdio.h>

#include "../ast/ast.h"

void codegen(ASTNode *node, FILE *output, int indent);

#endif //HEMATC_CODEGEN_H
