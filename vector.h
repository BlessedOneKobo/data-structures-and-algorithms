#include <stdbool.h>
#include <stddef.h>

#define VECTOR_INITIAL_CAPACITY 4

typedef struct {
    size_t size;
    size_t capacity;
    size_t itemSize;
    void *items;
    void (*freeItem)(void *);
    void (*printItem)(void *);
} Vector;

// Initialize Vector
void VectorInit(Vector *vector, size_t itemSize, void (*freeItem)(void *),
                void (*printItem)(void *));

// Number of items in vector
size_t VectorSize(Vector *vector);

// Number of items that can be held by [vector]
size_t VectorCapacity(Vector *vector);

// Check if [vector] has any items
bool VectorIsEmpty(Vector *vector);

// Returns the item at a given [index], fail if out of bounds
void *VectorAt(Vector *vector, size_t index);

// Add an [item] to the end of [vector]
void VectorPush(Vector *vector, void *item);

// Insert an [item] at [index], shifting the previous [index] and trailing
// items to the right
void VectorInsert(Vector *vector, size_t index, void *item);

// Insert an [item] at index 0
void VectorPrepend(Vector *vector, void *item);

// Remove an item from the end and return the value
void *VectorPop(Vector *vector);

// Delete the item at [index] and shift trailing items left
void VectorDelete(Vector *vector, size_t index);

// Remove all occurrences of [item]
void VectorRemove(Vector *vector, void *item);

// Find and return the first index of [item], return -1 if not found
int VectorFind(Vector *vector, void *item);

void VectorConcat(Vector *vector, Vector *other);

void VectorPrint(Vector *vector);

// Increase capacity
void __VectorResize(Vector *vector, size_t capacity);
