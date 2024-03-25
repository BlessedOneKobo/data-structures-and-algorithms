#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
} LList;

// Returns the number of elements in the list
size_t LListSize(LList *list);

// Returns true iff list is empty
bool LListEmpty(LList *list);

// Returns the value at nth item starting from 0
int LListValueAt(LList *list, size_t index);

// Add an item to the front of the list
void LListPushFront(LList *list, int value);

// Remove the front item and return its value
int LListPopFront(LList *list);

// Add an item at the end
void LListPushBack(LList *list, int value);

// Remove end item and return its value
int LListPopBack(LList *list);

// Get the value of the front item
int LListFront(LList *list);

// Get the value of the end item
int LListBack(LList *list);

// Insert [value] at [index], "shifting" the list to the right
void LListInsert(LList *list, int value, size_t index);

// Removes node at a given index
void LListErase(LList *list, size_t index);

// Returns the value of the node nth position from the end of the list
int LListValueNFromEnd(LList *list, size_t index);

// Reverses the list
void LListReverse(LList *list);

// Remove the first instance of [value] in the list
void LListRemoveValue(LList *list, int value);

// Display contents of linked list
void LListPrint(LList *list);
