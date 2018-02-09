#ifndef LINKED_LIST_INTERNAL_H
#define LINKED_LIST_INTERNAL_H

typedef struct LinkedListNode_ {
    void* data;
    struct LinkedListNode_* next;
} LinkedListNode_;

#endif // LINKED_LIST_INTERNAL_H
