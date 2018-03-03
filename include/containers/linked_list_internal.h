#ifndef LINKED_LIST_INTERNAL_H
#define LINKED_LIST_INTERNAL_H

#include <stdbool.h> // bool

typedef struct LinkedListNode_{
 
    void* data;
    struct LinkedListNode_* next;

#ifdef LL_DEBUG
    char* dbgStr;
#endif // LL_DEBUG

} LinkedListNode_;

void ll_debug_node_( LinkedListNode_ const*, char const* );

typedef enum VOID_PTR_TYPE_ {
     INT = 0,
     CSTRING
} VOID_PTR_TYPE_;

bool void_ptrs_equal_( void const* lhs, void const* rhs, VOID_PTR_TYPE_ type_tag );


#endif // LINKED_LIST_INTERNAL_H
