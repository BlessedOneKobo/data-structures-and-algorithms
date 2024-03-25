#include "llist.h"
#include <assert.h>
#include <stdio.h>

void can_push_back_to_empty_list();
void can_push_front_to_empty_list();
void can_push_back_to_non_empty_list();
void can_push_front_to_non_empty_list();
void can_erase_value_from_front();
void can_erase_value_from_back();
void can_erase_single_value_list();
void can_erase_value_from_middle();
void can_get_n_value_from_end();
void can_reverse();
void can_remove_value();
void can_insert_to_single_value_list();
void can_insert_to_back();
void can_insert_to_middle();

int main(void) {
    can_push_back_to_empty_list();
    can_push_front_to_empty_list();

    can_insert_to_single_value_list();
    can_insert_to_back();
    can_insert_to_middle();

    can_push_back_to_non_empty_list();
    can_push_front_to_non_empty_list();

    can_erase_value_from_front();
    can_erase_value_from_back();
    can_erase_single_value_list();
    can_erase_value_from_middle();

    can_get_n_value_from_end();

    can_reverse();

    can_remove_value();
}

void can_push_back_to_empty_list() {
    printf("can push back to empty list");

    LList numbers = {NULL};
    LListPushBack(&numbers, 1);
    assert(LListFront(&numbers) == 1);
    assert(LListBack(&numbers) == 1);

    puts("...OK");
}

void can_push_front_to_empty_list() {
    printf("can push front to empty list");

    LList numbers = {NULL};
    LListPushFront(&numbers, 1);
    assert(LListFront(&numbers) == 1);
    assert(LListBack(&numbers) == 1);

    puts("...OK");
}

void can_push_back_to_non_empty_list() {
    printf("can push back to non-empty list");

    LList numbers = {NULL};
    LListPushFront(&numbers, 1);
    LListPushFront(&numbers, 0);

    LListPushBack(&numbers, 9);
    assert(LListSize(&numbers) == 3);
    assert(LListValueAt(&numbers, 2) == 9);

    puts("...OK");
}

void can_push_front_to_non_empty_list() {
    printf("can push front to non empty list");

    LList numbers = {NULL};
    LListPushFront(&numbers, -1);
    LListPushFront(&numbers, -2);
    LListPushFront(&numbers, -3);
    LListPushFront(&numbers, -4);

    assert(LListSize(&numbers) == 4);
    assert(LListFront(&numbers) == -4);
    assert(LListBack(&numbers) == -1);

    puts("...OK");
}

void can_erase_value_from_front() {
    printf("can erase value from front");

    LList numbers = {NULL};
    LListPushFront(&numbers, -1);
    LListPushFront(&numbers, -2);
    LListPushFront(&numbers, -3);
    LListPushFront(&numbers, -4);

    LListErase(&numbers, 0);
    assert(LListSize(&numbers) == 3);
    assert(LListFront(&numbers) == -3);

    puts("...OK");
}

void can_erase_value_from_back() {
    printf("can erase value from back");

    LList numbers = {NULL};
    LListPushFront(&numbers, -1);
    LListPushFront(&numbers, -2);
    LListPushFront(&numbers, -3);
    LListPushFront(&numbers, -4);

    LListErase(&numbers, 3);
    assert(LListSize(&numbers) == 3);
    assert(LListBack(&numbers) == -2);

    puts("...OK");
}

void can_erase_single_value_list() {
    printf("can erase single value list");

    LList numbers = {NULL};
    LListPushFront(&numbers, -3);

    LListErase(&numbers, 0);
    assert(LListSize(&numbers) == 0);
    assert(numbers.head == NULL);

    puts("...OK");
}

void can_erase_value_from_middle() {
    printf("can erase value from middle");

    LList numbers = {NULL};
    LListPushFront(&numbers, -1);
    LListPushFront(&numbers, -2);
    LListPushFront(&numbers, -3);

    LListErase(&numbers, 1);
    assert(LListSize(&numbers) == 2);
    assert(numbers.head->next->value == -1);

    puts("...OK");
}

void can_get_n_value_from_end() {
    printf("can get n value from end");

    LList numbers = {NULL};
    LListPushFront(&numbers, -1);
    assert(LListValueNFromEnd(&numbers, 0) == -1);

    LListPushFront(&numbers, -2);
    assert(LListValueNFromEnd(&numbers, 0) == -1);
    assert(LListValueNFromEnd(&numbers, 1) == -2);

    LListPushFront(&numbers, -3);
    assert(LListValueNFromEnd(&numbers, 0) == -1);
    assert(LListValueNFromEnd(&numbers, 1) == -2);
    assert(LListValueNFromEnd(&numbers, 2) == -3);

    puts("...OK");
}

void can_reverse() {
    printf("can reverse");

    LList numbers = {NULL};
    LListPushFront(&numbers, -1);
    LListReverse(&numbers);
    assert(LListFront(&numbers) == -1);
    assert(LListBack(&numbers) == -1);

    LListPushFront(&numbers, -2);
    LListReverse(&numbers);
    assert(LListFront(&numbers) == -1);
    assert(LListBack(&numbers) == -2);
    LListReverse(&numbers);

    LListPushFront(&numbers, -3);
    LListReverse(&numbers);
    assert(LListFront(&numbers) == -1);
    assert(LListBack(&numbers) == -3);
    assert(LListValueAt(&numbers, 1) == -2);

    puts("...OK");
}

void can_remove_value() {
    printf("can remove value");

    LList numbers = {NULL};
    LListPushFront(&numbers, -1);
    LListRemoveValue(&numbers, -1);
    assert(LListSize(&numbers) == 0);

    LListPushFront(&numbers, -1);
    LListPushFront(&numbers, -2);
    LListRemoveValue(&numbers, -1);
    assert(LListSize(&numbers) == 1);
    assert(LListFront(&numbers) == -2);
    assert(LListBack(&numbers) == -2);

    LListPushFront(&numbers, -1);
    LListRemoveValue(&numbers, -2);
    assert(LListSize(&numbers) == 1);
    assert(LListFront(&numbers) == -1);
    assert(LListBack(&numbers) == -1);

    LListPushBack(&numbers, -2);
    LListPushBack(&numbers, -3);
    LListRemoveValue(&numbers, -2);
    assert(LListSize(&numbers) == 2);
    assert(LListFront(&numbers) == -1);
    assert(LListBack(&numbers) == -3);
    assert(numbers.head->next->value == LListBack(&numbers));

    puts("...OK");
}

void can_insert_to_single_value_list() {
    printf("can insert to single value list");

    LList numbers = {NULL};

    LListPushBack(&numbers, 1);
    LListInsert(&numbers, 0, 0);

    assert(LListFront(&numbers) == 0);
    assert(LListBack(&numbers) == 1);

    puts("...OK");
}

void can_insert_to_back() {
    printf("can insert to back");

    LList numbers = {NULL};

    LListPushBack(&numbers, 1);
    LListPushBack(&numbers, 2);
    LListInsert(&numbers, 3, 999);

    assert(LListBack(&numbers) == 3);

    puts("...OK");
}

void can_insert_to_middle() {
    printf("can insert to middle");

    LList numbers = {NULL};

    LListPushBack(&numbers, 1);
    LListPushBack(&numbers, 2);
    LListPushBack(&numbers, 3);
    LListInsert(&numbers, -2, 1);

    assert(LListValueAt(&numbers, 1) == -2);

    puts("...OK");
}
