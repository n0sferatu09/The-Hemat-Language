#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

Vector* create_vector(void) {
    Vector *vector = (Vector *)malloc(sizeof(Vector));
    if (!vector) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(-1);
    }

    vector->index = 0;
    vector->capacity = 8;
    vector->data = (char *)malloc(sizeof(char) * vector->capacity);
    if (!vector->data) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(vector);
        exit(-1);
    }

    return vector;
}

static void increase_size(Vector *vector) {
    vector->capacity *= 2;
    char *new_data = (char *)realloc(vector->data, sizeof(char) * vector->capacity);
    if (!new_data) {
        fprintf(stderr, "Memory reallocation failed!\n");
        free(vector->data);
        vector->data = NULL;
        vector->capacity = 0;
        exit(-1);
    }
    vector->data = new_data;
}

void vector_append(Vector *vector, char symbol) {
    if (!vector || !vector->data) return;

    if (vector->index + 1 >= vector->capacity) {
        increase_size(vector);
    }
    vector->data[vector->index++] = symbol;
    vector->data[vector->index] = '\0';
}

char* get_string(Vector *vector) {
    if (!vector || !vector->data) return "";
    return vector->data;
}

void vector_clear(Vector *vector) {
    if (!vector) return;
    vector->index = 0;
    if (vector->data) {
        vector->data[0] = '\0';
    }
}

void free_vector(Vector *vector) {
    if (vector) {
        free(vector->data);
        free(vector);
    }
}