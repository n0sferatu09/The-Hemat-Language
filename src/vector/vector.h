#ifndef HEMATC_VECTOR_H
#define HEMATC_VECTOR_H

typedef struct {
    char *data;
    int index;
    int capacity;
} Vector;

Vector* create_vector(void);
void vector_append(Vector* vector, char symbol);
char* get_string(Vector *vector);
void vector_clear(Vector *vector);
void free_vector(Vector* vector);

#endif //HEMATC_VECTOR_H
