#include "vector.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Initialize Vector
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

// Number of items in vector
size_t VectorSize(Vector *vector) { return vector->size; }

// Number of items that can be held by [vector]
size_t VectorCapacity(Vector *vector) { return vector->capacity; }

// Check if [vector] has any items
bool VectorIsEmpty(Vector *vector) { return vector->size == 0; }

// Returns the item at a given [index], fail if out of bounds
void *VectorAt(Vector *vector, size_t index) {
    assert(index >= 0 && index < vector->size);

    return (uint8_t *)vector->items + index * vector->itemSize;
}

// Add an [item] to the end of [vector]
void VectorPush(Vector *vector, void *item) {
    if (vector->size == vector->capacity)
        __VectorResize(vector, vector->capacity << 1);

    void *addr = (uint8_t *)vector->items + vector->size++ * vector->itemSize;
    memcpy(addr, item, vector->itemSize);
}

// Insert an [item] at [index], shifting the previous [index] and trailing
// items to the right
void VectorInsert(Vector *vector, size_t index, void *item) {
    assert(index >= 0 && index < vector->size);

    if (vector->size == vector->capacity)
        __VectorResize(vector, vector->capacity << 1);

    void *addr = (uint8_t *)vector->items + index * vector->itemSize;
    void *end = (uint8_t *)vector->items + vector->size * vector->itemSize;
    memmove((uint8_t *)addr + vector->itemSize, addr,
            (uint8_t *)end - (uint8_t *)addr);
    memcpy(addr, item, vector->itemSize);
}

// Insert an [item] at index 0
void VectorPrepend(Vector *vector, void *item) {
    if (vector->size == vector->capacity)
        __VectorResize(vector, vector->capacity << 1);

    VectorInsert(vector, 0, item);
}

// Remove an item from the end and return the value
void *VectorPop(Vector *vector) {
    return (uint8_t *)vector->items + --vector->size * vector->itemSize;
}

// Delete the item at [index] and shift trailing items left
void VectorDelete(Vector *vector, size_t index) {
    assert(index >= 0 && index < vector->size);

    void *addr = (uint8_t *)vector->items + index * vector->itemSize;
    void *end = (uint8_t *)vector->items + vector->size-- * vector->itemSize;
    if (vector->freeItem != NULL)
        vector->freeItem(addr);
    memmove(addr, (uint8_t *)addr + vector->itemSize,
            (uint8_t *)end - (uint8_t *)addr);
}

// Remove all occurrences of [item]
void VectorRemove(Vector *vector, void *item) {
    for (size_t i = 0; i < vector->size; i++) {
        void *addr = (uint8_t *)vector->items + i * vector->itemSize;
        if (memcmp(addr, item, vector->itemSize) == 0) {
            VectorDelete(vector, i--);
        }
    }
}

// Find and return the first index of [item], return -1 if not found
int VectorFind(Vector *vector, void *item) {
    for (size_t i = 0, size = vector->size; i < size; i++) {
        void *addr = (uint8_t *)vector->items + i * vector->itemSize;
        if (memcmp(addr, item, vector->itemSize))
            return i;
    }

    return -1;
}

// Increase capacity
void __VectorResize(Vector *vector, size_t newCapacity) {
    vector->items = realloc(vector->items, newCapacity * vector->itemSize);
    vector->capacity = newCapacity;
    assert(vector->items != NULL);
}
