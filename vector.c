#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/*
TODO:

- [x] size(v)
- [x] capacity(v)
- [x] is_empty(v)
- [x] at(v, index)
- [x] push(v)
- [x] insert(v, index, item)
- [x] prepend(v, item)
- [x] pop(v)
- [ ] delete(v, index)
- [ ] remove(v, item)
- [ ] find(v, item)
- [x] _resize(v, new_capacity)

Clean by:

- [x] Create a test file
- [x] using a header file
- [x] Use a makefile
*/

vector *create_vector(){
    vector *v = malloc(sizeof(vector)); // Memory needs to be allocated when
                                        // returning references of locally
                                        // initialized variables. 
    v->capacity = VECTOR_INIT_SIZE;
    v->size = 0;
    v->data = malloc(sizeof(int) * v->capacity);
    return v;
}

int sizeof_vector(vector *v){
    return v->size;
}

int capacity_of_vector(vector *v){
    return v->capacity;
}

bool vector_is_empty(vector *v){
    return v->size == 0;
}

int vector_at(vector *v, int index){
    int *addr = v->data + (index * sizeof(int));
    if (0 <= index && index < v->size)
        return *(addr);
    printf("Reading from forbidden memory! Exiting!\n");
    exit(1);
}

void resize_vector(vector *v, int new_capacity){
    void *data = realloc(v->data, sizeof(int) * new_capacity);
    v->data = data;
    v->capacity = new_capacity;
}

void push_in_vector(vector *v, int item){
    if (v->size == v->capacity)
        resize_vector(v, 2*v->capacity);
    int *new_addr = v->data + (v->size++ * sizeof(int));
    *(new_addr) = item;
}

void insert_in_vector(vector *v, int index, int item){
    if (0<=index && index<v->size){
        if (v->size == v->capacity)
            resize_vector(v, 2*v->capacity);

        for (int i=v->size-1; i>=index; i--)
            *(int *)(v->data + (i+1) * sizeof(int)) = vector_at(v, i);

        *(int *)(v->data + index*sizeof(int)) = item;

        v->size++;
    }
}

void prepend_in_vector(vector *v, int item){
    if (v->size == v->capacity)
        resize_vector(v, 2*v->capacity);

    for(int i=0; i<v->size; i++)
        *(int *)(v->data + (i+1) * sizeof(int)) = vector_at(v, i);

    *(int *)(v->data) = item;
    v->size = v->size + 1;
}

int pop_vector(vector *v){
    if (v->size >= 1){
        int *last_addr = v->data + (v->size-- - 1) * sizeof(int);
        return *(last_addr);
    }
    printf("Popping array of length 0. Exiting!");
    exit(1);
}
