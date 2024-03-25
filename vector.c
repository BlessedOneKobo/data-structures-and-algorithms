#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void VectorInit(Vector *vector, size_t itemSize, void (*freeItem)(void *),
                void (*printItem)(void *)) {
    vector->size = 0;
    vector->capacity = VECTOR_INITIAL_CAPACITY;
    vector->itemSize = itemSize;
    vector->freeItem = freeItem;
    vector->printItem = printItem;
    vector->items = malloc(itemSize * VECTOR_INITIAL_CAPACITY);
    assert(vector->items != NULL);
}

size_t VectorSize(Vector *vector) { return vector->size; }

size_t VectorCapacity(Vector *vector) { return vector->capacity; }

bool VectorIsEmpty(Vector *vector) { return vector->size == 0; }

void *VectorAt(Vector *vector, size_t index) {
    assert(index >= 0 && index < vector->size);

    return (uint8_t *)vector->items + index * vector->itemSize;
}

void VectorPush(Vector *vector, void *item) {
    if (vector->size == vector->capacity)
        __VectorResize(vector, vector->capacity << 1);

    void *addr = (uint8_t *)vector->items + vector->size * vector->itemSize;
    memcpy(addr, item, vector->itemSize);
    vector->size++;
}

void VectorInsert(Vector *vector, size_t index, void *item) {
    assert(index >= 0);
    if (vector->size > 0)
        assert(index < vector->size);

    if (vector->size == vector->capacity)
        __VectorResize(vector, vector->capacity << 1);

    void *addr = (uint8_t *)vector->items + index * vector->itemSize;
    void *end = (uint8_t *)vector->items + vector->size * vector->itemSize;
    memmove((uint8_t *)addr + vector->itemSize, addr,
            (uint8_t *)end - (uint8_t *)addr);
    memcpy(addr, item, vector->itemSize);
    vector->size++;
}

void VectorPrepend(Vector *vector, void *item) {
    if (vector->size == vector->capacity)
        __VectorResize(vector, vector->capacity << 1);

    VectorInsert(vector, 0, item);
}

void *VectorPop(Vector *vector) {
    return (uint8_t *)vector->items + --vector->size * vector->itemSize;
}

void VectorDelete(Vector *vector, size_t index) {
    assert(index >= 0 && index < vector->size);

    void *addr = (uint8_t *)vector->items + index * vector->itemSize;
    if (vector->freeItem != NULL)
        vector->freeItem(addr);

    if (index == vector->size - 1) {
        VectorPop(vector);
        return;
    }

    void *end = (uint8_t *)vector->items + vector->size * vector->itemSize;
    memmove(addr, (uint8_t *)addr + vector->itemSize,
            (uint8_t *)end - (uint8_t *)addr);
    vector->size--;
}

void VectorRemove(Vector *vector, void *item) {
    for (size_t i = 0; i < vector->size; i++) {
        void *addr = (uint8_t *)vector->items + i * vector->itemSize;
        if (memcmp(addr, item, vector->itemSize) == 0) {
            VectorDelete(vector, i--);
        }
    }
}

int VectorFind(Vector *vector, void *item) {
    for (size_t i = 0, size = vector->size; i < size; i++) {
        void *addr = (uint8_t *)vector->items + i * vector->itemSize;
        if (memcmp(addr, item, vector->itemSize) == 0)
            return i;
    }

    return -1;
}

void VectorConcat(Vector *vector, Vector *other) {
    assert(vector->itemSize == other->itemSize);

    size_t newVectorSize = vector->size + other->size;
    while (newVectorSize > vector->capacity) {
        __VectorResize(vector, vector->capacity << 1);
    }

    void *addr = (uint8_t *)vector->items + vector->size * vector->itemSize;
    memcpy(addr, other->items, other->size * other->itemSize);
    vector->size = newVectorSize;
}

void VectorPrint(Vector *vector) {
    assert(vector->printItem != NULL);

    for (size_t i = 0; i < vector->size; i++) {
        void *addr = (uint8_t *)vector->items + i * vector->itemSize;
        vector->printItem(addr);
    }
}

void __VectorResize(Vector *vector, size_t newCapacity) {
    vector->items = realloc(vector->items, newCapacity * vector->itemSize);
    vector->capacity = newCapacity;
    assert(vector->items != NULL);
}
