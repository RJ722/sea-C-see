#include <stdbool.h>

#define VECTOR_INIT_SIZE 8

// #define CREATE_VECTOR() create_vector
// #define SIZEOF_VECTOR(vec) vector vec; sizeof_vector(&vec)
// #define CAPACTIY_OF_VECTOR(vec) capacity_of_vector(&vec)
// #define VECTOR_IS_EMPTY(vec) vector_is_empty(&vec)
// #define VECTOR_AT(vec, index) vector_at(&vec, index)
// #define PUSH_IN_VECTOR(vec, item) push_in_vector(&vec, item)
// #define INSERT_IN_VECTOR(vec, index, item) insert_in_vec(&vec, index, item)
// #define PREPEND_IN_VECTOR(vec, item) prepend_in_vector(&vec, item)

typedef struct vector{
    int capacity;
    int size;
    void *data;
} vector;

vector *create_vector();

int sizeof_vector(vector *);
int capacity_of_vector(vector *);
bool vector_is_empty(vector *);
int vector_at(vector *, int);
void resize_vector(vector *, int);
void push_in_vector(vector *, int);
void insert_in_vector(vector *, int, int);
void prepend_in_vector(vector *, int);
int pop_vector(vector *);
