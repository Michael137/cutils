#ifndef LINKED_LIST_INTERNAL_H
#define LINKED_LIST_INTERNAL_H

typedef struct LinkedListNode_{
 
    void* data;
    struct LinkedListNode_* next;

#ifdef LL_DEBUG
    char* dbgStr;
#endif // LL_DEBUG

} LinkedListNode_;

void ll_debug_node_( LinkedListNode_ const*, char const* );

#endif // LINKED_LIST_INTERNAL_H
