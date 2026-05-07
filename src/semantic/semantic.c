#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../symbol_table/symbol_table.h"
#include "../ast/ast.h"
#include "../lexer/tokens/tokens.h"
#include "semantic.h"

static bool has_error = false;
static int loop_depth = 0;

void semantic_error(const char *message, ASTNode *node) {
    has_error = true;
    fprintf(stderr, "Semantic Error: %s", message);

    if (node) {
        if (node->string_value) {
            fprintf(stderr, " (near '%s')", node->string_value);
        } else if (node->type == NUMBER_LITERAL) {
            fprintf(stderr, " (near '%lld')", node->int_value);
        }
    }

    fprintf(stderr, "\n");
}

static DataType get_expression_type(ASTNode *node, SymbolTable *symbol_table) {
    if (!node) return TYPE_UNKNOWN;

    switch (node->type) {
        case NUMBER_LITERAL:
            return TYPE_INTEGER;

        case STRING_LITERAL:
            return TYPE_STRING;

        case IDENTIFIER: {
            Symbol *symbol = lookup_symbol(symbol_table, node->string_value);
            if (!symbol) {
                semantic_error("Undeclared variable", node);
                return TYPE_UNKNOWN;
            }

            return symbol->type;
        }

        case BINARY_EXPRESSION: {
            DataType left = get_expression_type(node->left, symbol_table);
            DataType right = get_expression_type(node->right, symbol_table);

            if (left == TYPE_UNKNOWN || right == TYPE_UNKNOWN) {
                return TYPE_UNKNOWN;
            }

            int operator = node->int_value;

            if (operator == ADD || operator == SUB ||
                operator == MULT || operator == DIV) {
                if (left == right) {
                    node->data_type = TYPE_INTEGER;
                    return TYPE_INTEGER;
                }
                semantic_error("Arithmetic operators require integer operands", node);
                return TYPE_UNKNOWN;

            }

            if (operator == GT || operator == LT ||
                operator == EQ || operator == NEQ) {
                if (left == right) {
                    node->data_type = TYPE_INTEGER;
                    return TYPE_INTEGER;
                }
                semantic_error("Comparison operators require operands of the same type", node);
                return TYPE_UNKNOWN;
            }

            semantic_error("Unknown binary operator", node);
            return TYPE_UNKNOWN;
        }

        case UNARY_MINUS: {
            DataType expr_type = get_expression_type(node->right, symbol_table);

            if (expr_type == TYPE_INTEGER) {
                node->data_type = TYPE_INTEGER;
                return TYPE_INTEGER;
            }

            semantic_error("Unary minus requires integer operand", node);
            return TYPE_UNKNOWN;
        }

        default:
            return TYPE_UNKNOWN;
    }
}

static void traverse_and_declare(ASTNode *node, SymbolTable *symbol_table) {
    if (!node) return;

    switch (node->type) {
        case LET_STATEMENT: {
            DataType type = get_expression_type(node->right, symbol_table);

            if (type == TYPE_UNKNOWN) {
                semantic_error("Unknown type", node);
                return;
            }

            node->data_type = type;
            symbol_table_insert(symbol_table, node->string_value, type);
            traverse_and_declare(node->right, symbol_table);
            traverse_and_declare(node->next, symbol_table);
            return;
        }

        case ASSIGNMENT_STATEMENT:
            traverse_and_declare(node->next, symbol_table);
            return;

        default:
            traverse_and_declare(node->left, symbol_table);
            traverse_and_declare(node->right, symbol_table);
            traverse_and_declare(node->next, symbol_table);
    }
}

static void traverse_and_check(ASTNode *node, SymbolTable *symbol_table) {
    if (!node) return;

    switch (node->type) {
        case PROGRAM:
            traverse_and_check(node->right, symbol_table);
            traverse_and_check(node->next, symbol_table);
            return;

        case IDENTIFIER: {
            if (!lookup_symbol(symbol_table, node->string_value)) {
                semantic_error("Undeclared variable", node);
                return;
            }

            traverse_and_check(node->next, symbol_table);
            return;
        }

        case ASSIGNMENT_STATEMENT: {
            Symbol *symbol = lookup_symbol(symbol_table, node->string_value);
            if (!symbol) {
                semantic_error("Assignment to undeclared variable", node);
                return;
            }

            DataType expr_type = get_expression_type(node->right, symbol_table);

            if (expr_type != symbol->type) {
                semantic_error("Type mismatch in assignment", node);
                return;
            }

            node->data_type = symbol->type;
            traverse_and_check(node->next, symbol_table);
            return;
        }

        case PRINT_STATEMENT: {
            DataType type = get_expression_type(node->right, symbol_table);
            if (type == TYPE_UNKNOWN) {
                semantic_error("Unknown type for print statement!", node);
                return;
            }
            node->data_type = type;
            traverse_and_check(node->next, symbol_table);
            return;
        }

        case IF_STATEMENT: {
            DataType type = get_expression_type(node->left, symbol_table);
            if (type != TYPE_INTEGER) {
                semantic_error("If condition must be integer!", node);
                return;
            }

            traverse_and_check(node->right, symbol_table);
            traverse_and_check(node->next, symbol_table);
            return;
        }

        case LOOP_STATEMENT: {
            loop_depth++;
            traverse_and_check(node->right, symbol_table);
            loop_depth--;
            traverse_and_check(node->next, symbol_table);
            return;
        }

        case BREAK_STATEMENT: {
            if (loop_depth == 0) {
                fprintf(stderr, "Error: break statement outside the loop\n");
                has_error = true;
                return;
            }

            traverse_and_check(node->next, symbol_table);
            return;
        }

        default:
            traverse_and_check(node->left, symbol_table);
            traverse_and_check(node->right, symbol_table);
            traverse_and_check(node->next, symbol_table);
            return;

    }
}

bool semantic_analyze(ASTNode *ast, SymbolTable *symbol_table) {
    has_error = false;

    traverse_and_declare(ast, symbol_table);

    if (!has_error) {
        traverse_and_check(ast, symbol_table);
    }

    return !has_error;
}