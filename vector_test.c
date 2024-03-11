#include "vector.h"
#include <assert.h>
#include <stdio.h>

void can_initialize_without_deallocator_and_printer() {
    printf("Can initialize without deallocator and printer");

    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);
    assert(VectorSize(&numbers) == 0);
    assert(VectorCapacity(&numbers) == VECTOR_INITIAL_CAPACITY);
    assert(numbers.itemSize == sizeof(int));
    assert(numbers.freeItem == NULL);
    assert(numbers.printItem == NULL);

    printf("...OK\n");
}

void can_push_values() {
    printf("Can push values");

    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);
    for (size_t i = 0; i < 4; i++)
        VectorPush(&numbers, &i);
    assert(VectorSize(&numbers) == 4);
    assert(*((int *)VectorAt(&numbers, 0)) == 0);
    assert(*((int *)VectorAt(&numbers, 3)) == 3);

    printf("...OK\n");
}

void can_increase_capacity() {
    printf("Can increase capacity");

    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);
    for (size_t i = 0; i < 10; i++)
        VectorPush(&numbers, &i);
    assert(*((int *)VectorAt(&numbers, 4)) == 4);
    assert(VectorSize(&numbers) == 10);
    assert(VectorCapacity(&numbers) > VECTOR_INITIAL_CAPACITY);
    printf("...OK\n");
}

int main(void) {
    printf("TESTING vector.c\n");
    can_initialize_without_deallocator_and_printer();
    can_push_values();
    can_increase_capacity();
}
