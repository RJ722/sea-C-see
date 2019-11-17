#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define VECTOR_INIT_SIZE 8

typedef struct vector{
    int capacity;
    int size;
    void *data;
} vector;

/*
TODO:

- [x] size(v)
- [x] capacity(v)
- [x] is_empty(v)
- [x] at(v, index)
- [x] push(v)
- [x] insert(v, index, item)
- [x] prepend(v, item)
- [ ] pop(v)
- [ ] delete(v, index)
- [ ] remove(v, item)
- [ ] find(v, item)
- [x] _resize(v, new_capacity)

Clean by:

- [ ] Create a test file
- [ ] using a header file
- [ ] Use a makefile
- [ ] Print additional info in DEBUG mode using `CFLAGS -DDEBUG_ON`
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

void _resize_vector(vector *v, int new_capacity){
    void *data = realloc(v->data, sizeof(int) * new_capacity);
    v->data = data;
    v->capacity = new_capacity;
}

void push_in_vector(vector *v, int item){
    if (v->size == v->capacity)
        _resize_vector(v, 2*v->capacity);
    int *new_addr = v->data + (v->size++ * sizeof(int));
    *(new_addr) = item;
}

void insert_in_vector(vector *v, int index, int item){
    if (0<=index && index<v->size){
        if (v->size == v->capacity)
            _resize_vector(v, 2*v->capacity);

        for (int i=v->size-1; i>=index; i--)
            *(int *)(v->data + (i+1) * sizeof(int)) = vector_at(v, i);

        *(int *)(v->data + index*sizeof(int)) = item;

        v->size++;
    }
}

void prepend_in_vector(vector *v, int item){
    if (v->size == v->capacity)
        _resize_vector(v, 2*v->capacity);

    for(int i=0; i<v->size; i++)
        *(int *)(v->data + (i+1) * sizeof(int)) = vector_at(v, i);

    *(int *)(v->data) = item;
    v->size = v->size + 1;
}

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

    _resize_vector(v, 32);
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

int main(){
    // test_vector_interactively();
    test_resize_vector();
    test_vector_is_empty();
    test_vector_autoresizes_on_push();
    test_insert_in_middle();
    test_prepend_in_vector();

    return 0;
}
