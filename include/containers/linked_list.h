#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <containers/linked_list_internal.h>

#include <stdbool.h> // bool
#include <stddef.h> // size_t

// Linked List Constats
#define LL_FAILURE     -1
#define LL_SUCCESS      1
#define LL_INVALID_ARGS 2

// Linked List Externals
typedef struct LinkedList_ {
    LinkedListNode_ *head,
                    *tail;
    size_t size;

#ifdef LL_DEBUG
    char* dbgStr;
#endif // LL_DEBUG
} LinkedList;

// External methods
bool ll_push_front( LinkedList**, void const*, const size_t );
bool ll_pop_front( LinkedList** );
bool ll_remove( LinkedList**, const size_t );
bool ll_free( LinkedList** );
void* ll_at( LinkedList const*, const size_t );
bool ll_find();
bool ll_sort();
bool ll_create( LinkedList** );
size_t ll_size( LinkedList const* );
void ll_debug( LinkedList const*, char const* );

#endif // LINKED_LIST_H
