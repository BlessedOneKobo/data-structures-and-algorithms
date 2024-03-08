// Spec and Interface:
// https://github.com/jwasham/coding-interview-university?tab=readme-ov-file#arrays

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 4

typedef struct {
    size_t size;
    size_t item_size;
    size_t capacity;
    void *items;
    void (*dealloc_item)(void *);
    void (*print_item)(void *);
} Vector;

void VectorInit(Vector *vector, size_t item_size, void (*dealloc_item)(void *),
                void (*print_item)(void *));
size_t VectorSize(Vector *vector);
size_t VectorCapacity(Vector *vector);
bool VectorIsEmpty(Vector *vector);
void *VectorAt(Vector *vector, int index);
void VectorPush(Vector *vector, void *item);
void VectorInsert(Vector *vector, int index, void *item);
void VectorPrepend(Vector *vector, void *item);
void *VectorPop(Vector *vector);
void VectorDelete(Vector *vector, int index);
void VectorRemove(Vector *vector, void *item);
size_t VectorFind(Vector *vector, void *item);
void __VectorResize(Vector *vector, size_t new_capacity);

int main(int argc, char *argv[]) {
    printf("hello, world");
    return 0;
}
