#include "vector.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

void can_initialize_without_deallocator_and_printer() {
    printf("can initialize without deallocator and printer");

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
    printf("can push values");

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
    printf("can increase capacity");

    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);
    for (size_t i = 0; i < 10; i++)
        VectorPush(&numbers, &i);
    assert(*((int *)VectorAt(&numbers, 4)) == 4);
    assert(VectorSize(&numbers) == 10);
    assert(VectorCapacity(&numbers) > VECTOR_INITIAL_CAPACITY);

    printf("...OK\n");
}

void can_insert() {
    printf("can insert");

    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);
    for (size_t i = 0; i < 10; i++)
        VectorPush(&numbers, &i);
    int n = 9000;
    VectorInsert(&numbers, 2, &n);

    assert(numbers.size == 11);
    assert(*((int *)VectorAt(&numbers, 2)) == 9000);
    assert(*((int *)VectorAt(&numbers, 1)) == 1);
    assert(*((int *)VectorAt(&numbers, 3)) == 2);

    printf("...OK\n");
}

void can_prepend() {
    printf("can prepend");

    int n = -12;
    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);

    VectorPrepend(&numbers, &n);
    assert(numbers.size == 1);
    assert(*((int *)VectorAt(&numbers, 0)) == -12);

    n = -18;
    VectorPrepend(&numbers, &n);
    assert(numbers.size == 2);
    assert(*((int *)VectorAt(&numbers, 0)) == -18);

    printf("...OK\n");
}

void can_pop() {
    printf("can pop");

    int *p = NULL;
    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);
    for (size_t i = 0; i < 10; i++)
        VectorPush(&numbers, &i);

    p = VectorPop(&numbers);
    assert(numbers.size == 9);
    assert(*p == 9);

    printf("...OK\n");
}

void can_delete() {
    printf("can delete from");

    Vector numbers = {0};
    VectorInit(&numbers, sizeof(int), NULL, NULL);
    for (size_t i = 0; i < 10; i++)
        VectorPush(&numbers, &i);

    VectorDelete(&numbers, 0);
    assert(*((int *)VectorAt(&numbers, 0)) == 1);
    assert(numbers.size == 9);

    VectorDelete(&numbers, numbers.size - 1);
    assert(*((int *)VectorAt(&numbers, numbers.size - 1)) == 8);
    assert(numbers.size == 8);

    VectorDelete(&numbers, 3);
    assert(*((int *)VectorAt(&numbers, 3)) == 5);
    assert(numbers.size == 7);

    printf("...OK\n");
}

// TODO
void can_remove() {}

// TODO
void can_find() {}

void print_int(void *item) { printf("[ %d ]\n", *(int *)item); }

void can_concatenate() {
    printf("can concatenate a vector with the same itemSize");

    Vector numbers = {0};
    Vector positiveNumbers = {0};

    VectorInit(&numbers, sizeof(int), NULL, print_int);
    VectorInit(&positiveNumbers, sizeof(int), NULL, NULL);

    for (size_t i = 1; i <= 10; i++) {
        int neg = i * -1;
        VectorPush(&numbers, &neg);
        VectorPush(&positiveNumbers, &i);
    }

    VectorConcat(&numbers, &positiveNumbers);
    assert(numbers.size == 20);
    assert(((int *)numbers.items)[0] == -1);
    assert(((int *)numbers.items)[numbers.size - 1] == 10);

    printf("...OK\n");
}

int main(void) {
    printf("TESTING vector.c\n");
    can_initialize_without_deallocator_and_printer();
    can_push_values();
    can_increase_capacity();
    can_concatenate();
    can_insert();
    can_prepend();
    can_pop();
    can_delete();
}
