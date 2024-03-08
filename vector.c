// Spec and Interface:
// https://github.com/jwasham/coding-interview-university?tab=readme-ov-file#arrays

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
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
int VectorFind(Vector *vector, void *item);
void VectorDestroy(Vector *vector);
void __VectorResize(Vector *vector, size_t new_capacity);

void VectorInit(Vector *vector, size_t item_size, void (*dealloc_item)(void *),
                void (*print_item)(void *)) {
    vector->size = 0;
    vector->item_size = item_size;
    vector->capacity = INITIAL_CAPACITY;
    vector->dealloc_item = dealloc_item;
    vector->print_item = print_item;
    vector->items = malloc(INITIAL_CAPACITY * item_size);
    assert(vector->items != NULL);
}

size_t VectorSize(Vector *vector) { return vector->size; }

size_t VectorCapacity(Vector *vector) { return vector->capacity; }

bool VectorIsEmpty(Vector *vector) { return vector->size == 0; }

void *VectorAt(Vector *vector, int index) {
    assert(index >= 0 && index < vector->size);

    return (uint8_t *)vector->items + index * vector->item_size;
}

void VectorPush(Vector *vector, void *item) {
    if (vector->size == vector->capacity) {
        __VectorResize(vector, vector->capacity << 1);
    }

    void *addr = (char *)vector->items + vector->size++ * vector->item_size;
    memcpy(addr, item, vector->item_size);
}

void VectorInsert(Vector *vector, int index, void *item) {
    assert(index >= 0 && index < vector->size);

    if (vector->size == vector->capacity) {
        __VectorResize(vector, vector->capacity << 1);
    }

    void *addr = (uint8_t *)vector->items + index * vector->item_size;
    void *end = (uint8_t *)vector->items + vector->size * vector->item_size;
    memmove((uint8_t *)addr + vector->item_size, addr,
            (uint8_t *)end - (uint8_t *)addr);
    memcpy(addr, item, vector->item_size);
    vector->size++;
}

void VectorPrepend(Vector *vector, void *item) {
    VectorInsert(vector, 0, item);
}

void *VectorPop(Vector *vector) {
    if (vector->size == 0)
        return NULL;

    return (uint8_t *)vector->items + --vector->size * vector->item_size;
}

void VectorDelete(Vector *vector, int index) {
    assert(index >= 0 && index < vector->size);

    void *addr = (uint8_t *)vector->items + index * vector->item_size;
    void *end = (uint8_t *)vector->items + vector->size * vector->item_size;

    if (vector->dealloc_item != NULL) {
        vector->dealloc_item(addr);
    }

    memmove(addr, (uint8_t *)addr + vector->item_size,
            (uint8_t *)end - (uint8_t *)addr);
    vector->size--;
}

void VectorRemove(Vector *vector, void *item) {
    for (size_t i = 0; i < vector->size; i++) {
        void *addr = (uint8_t *)vector->items + i * vector->item_size;
        if (memcmp(addr, item, vector->item_size) == 0) {
            VectorDelete(vector, i);
            break;
        }
    }
}

int VectorFind(Vector *vector, void *item) {
    for (int i = 0; i < vector->size; i++) {
        void *addr = (uint8_t *)vector->items + i * vector->item_size;
        if (memcmp(addr, item, vector->item_size) == 0)
            return i;
    }

    return -1;
}

void VectorPrint(Vector *vector) {
    for (size_t i = 0; i < vector->size; i++)
        vector->print_item((uint8_t *)vector->items + i * vector->item_size);
}

void VectorDestroy(Vector *vector) {
    if (vector->dealloc_item) {
        for (size_t i = 0; i < vector->size; i++) {
            void *item = (uint8_t *)vector->items + i * vector->item_size;
            vector->dealloc_item(item);
        }
    }

    vector->size = 0;
}

void __VectorResize(Vector *vector, size_t new_capacity) {
    assert(new_capacity > vector->capacity);

    vector->capacity = new_capacity;
    vector->items = realloc(vector->items, new_capacity * vector->item_size);
    assert(vector->items != NULL);
}

// Printers
void print_int(void *vp) { printf(" < %d > ", *(int *)vp); }
void print_string(void *vp) {
    char *str = *(char **)vp;
    printf(" <'%s'> ", str);
}

void dealloc_string(void *vp) { free(*(char **)vp); }

int main(int argc, char *argv[]) {
    assert(argc > 1);

    Vector arguments = {0};
    VectorInit(&arguments, sizeof(char *), dealloc_string, print_string);
    for (int i = 1; i < argc; i++) {
        char *item = strdup(argv[i]);
        VectorPush(&arguments, &item);
    }
    VectorPrint(&arguments);

    printf("\nafter delete:\n");
    // for (size_t i = 0; i < 5; i++)
    // VectorDelete(&arguments, 2);
    VectorDestroy(&arguments);
    VectorPrint(&arguments);

    return 0;
}
