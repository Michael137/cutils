#ifndef LINKED_LIST_INTERNAL_H
#define LINKED_LIST_INTERNAL_H

typedef struct LinkedListNode_ {
    void* data;
    LinkedListNode_* next;
} LinkedListNode_;

#endif // LINKED_LIST_INTERNAL_H
