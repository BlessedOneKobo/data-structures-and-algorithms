#include "llist.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

size_t LListSize(LList *list) {
    size_t count = 0;
    Node *iter = list->head;
    while (iter != NULL) {
        count++;
        iter = iter->next;
    }
    return count;
}

bool LListEmpty(LList *list) { return list->head == NULL; }

int LListValueAt(LList *list, size_t index) {
    assert(index >= 0);

    Node *iter = list->head;
    while (index > 0 && iter != NULL) {
        --index;
        iter = iter->next;
    }
    assert(iter != NULL);

    return iter->value;
}

void LListPushFront(LList *list, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    assert(node != NULL);

    node->value = value;
    node->next = list->head;
    list->head = node;
}

int LListPopFront(LList *list) {
    assert(list->head != NULL);

    Node *prevHead = list->head;
    int value = prevHead->value;

    list->head = prevHead->next;
    free(prevHead);
    return value;
}

void LListPushBack(LList *list, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    assert(node != NULL);
    node->value = value;
    node->next = NULL;

    if (list->head == NULL) {
        list->head = node;
        return;
    }

    Node *prev = NULL;
    Node *iter = list->head;

    while (iter != NULL) {
        prev = iter;
        iter = iter->next;
    }

    if (prev == NULL)
        iter->next = node;
    else
        prev->next = node;
}

int LListPopBack(LList *list) {
    assert(list->head != NULL);

    Node *prev = NULL;
    Node *iter = list->head;

    while (iter->next != NULL) {
        prev = iter;
        iter = iter->next;
    }

    if (prev == NULL)
        list->head = NULL;
    else
        prev->next = iter->next;

    int value = iter->value;
    free(iter);
    return value;
}

int LListFront(LList *list) {
    assert(list->head != NULL);

    return list->head->value;
}

int LListBack(LList *list) {
    assert(list->head != NULL);

    Node *iter = list->head;
    while (iter->next != NULL)
        iter = iter->next;
    return iter->value;
}

void LListInsert(LList *list, int value, size_t index) {
    assert(index >= 0 && list->head != NULL);

    if (index == 0) {
        LListPushFront(list, value);
        return;
    }

    Node *node = (Node *)malloc(sizeof(Node));
    assert(node != NULL);
    node->value = value;
    node->next = NULL;

    Node *prev = NULL;
    Node *iter = list->head;

    while (index > 0 && iter != NULL) {
        index--;
        prev = iter;
        iter = iter->next;
    }

    if (iter == NULL) {
        LListPushBack(list, value);
        return;
    }

    prev->next = node;
    node->next = iter;
}

void LListErase(LList *list, size_t index) {
    assert(index >= 0 && list->head != NULL);

    Node *prev = NULL;
    Node *iter = list->head;

    while (index > 0 && iter != NULL) {
        index--;
        prev = iter;
        iter = iter->next;
    }
    assert(iter != NULL);

    if (prev == NULL)
        list->head = iter->next;
    else
        prev->next = iter->next;
    free(iter);
}

int LListValueNFromEnd(LList *list, size_t n) {
    assert(n >= 0 && list->head != NULL);

    size_t size = LListSize(list);
    assert(size - 1 >= n);

    return LListValueAt(list, size - 1 - n);
}

void LListReverse(LList *list) {
    assert(list->head != NULL);

    if (list->head->next == NULL)
        return;

    Node *back = list->head;
    while (back->next != NULL)
        back = back->next;

    Node *iter = list->head;
    while (iter != back) {
        Node *next = iter->next;
        iter->next = back->next;
        back->next = iter;
        iter = next;
    }
    list->head = back;
}

void LListRemoveValue(LList *list, int value) {
    assert(list->head != NULL);

    Node *prev = NULL;
    Node *iter = list->head;

    while (iter->next != NULL) {
        if (iter->value == value)
            break;
        prev = iter;
        iter = iter->next;
    }

    if (iter->value != value)
        return;

    if (prev)
        prev->next = iter->next;
    else
        list->head = iter->next;
    free(iter);
}

void LListPrint(LList *list) {
    Node *iter = list->head;
    while (iter != NULL) {
        printf("< %d > -> ", iter->value);
        iter = iter->next;
    }
    printf("<X>\n");
}