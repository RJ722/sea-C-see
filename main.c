#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "vector.h"

void test_vector_interactively(){
    vector *arr = create_vector();
    int n, input;

    printf("Length of array: ");
    scanf("%d", &n);

    for(int i=0; i<n; i++){
        scanf("%d", &input);
        push_in_vector(arr, input);
    }

    for (int i = 0; i < n; i++)
        printf("%d\n", vector_at(arr, i));
}

void test_resize_vector(){
    vector *v = create_vector();

    assert(v->capacity == VECTOR_INIT_SIZE);

    for (int i=0; i<VECTOR_INIT_SIZE; i++)
        push_in_vector(v, 10*i);

    resize_vector(v, 32);
    assert (v->capacity == 32);

    for (int i=0; i<(32 - VECTOR_INIT_SIZE); i++)
        push_in_vector(v, 9*i);

    for (int i=0; i<32; i++){
        if (i<8)
            assert(vector_at(v, i) == 10*i);
        else
            assert(vector_at(v, i) == 9*(i-8));
    }

    printf("[INFO] Successfully passed 'test_resize_vector'.\n");
}

void test_vector_autoresizes_on_push(){
    vector *v = create_vector();

    assert(v->capacity == VECTOR_INIT_SIZE);

    for (int i=0; i<VECTOR_INIT_SIZE*2; i++)
        push_in_vector(v, 10*i);

    assert (v->capacity == 16);
    printf("[INFO] Successfully passed 'test_vector_autoresizes_on_push'.\n");
}

void test_vector_is_empty(){
    vector *v = create_vector();
    assert(vector_is_empty(v) == 1);
    printf("[INFO] Successfully passed 'test_vector_is_empty.'\n");
}

void test_insert_in_middle(){
    vector *v = create_vector();

    push_in_vector(v, 0);
    push_in_vector(v, 2);
    push_in_vector(v, 3);

    insert_in_vector(v, 1, 1);

    for(int i=0; i<4; i++)
        assert(vector_at(v, i) == i);

    printf("[INFO] Successfully passed 'test_insert_in_middle'.\n");
}

void test_prepend_in_vector(){
    vector *v = create_vector();

    for (int i=1; i<9; i++)
        push_in_vector(v, 2*i);

    prepend_in_vector(v, 0);

    assert(v->capacity == 16);
    assert(v->size == 9);

    for (int i=0; i<9; i++)
        push_in_vector(v, 2*i);
    
    printf("[INFO] Successfully passed 'test_prepend_in_vector'.\n");
}

void test_vector_pop(){
    vector *v = create_vector();

    push_in_vector(v, 10);
    assert(v->size == 1);

    int a = pop_vector(v);
    assert(a == 10);
    assert(v->size == 0);
    printf("[INFO] Successfully passed 'test_vector_pop'.\n");
}

int main(){
    // test_vector_interactively();
    test_resize_vector();
    test_vector_is_empty();
    test_vector_autoresizes_on_push();
    test_insert_in_middle();
    test_prepend_in_vector();
    test_vector_pop();

    return 0;
}
