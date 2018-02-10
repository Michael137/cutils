#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <containers/linked_list_internal.h>

#include <stdbool.h> // bool
#include <stddef.h> // size_t

// Linked List Externals
typedef struct LinkedList_ {
    LinkedListNode_ *head,
                    *tail;
    size_t size;

#ifdef LL_DEBUG
    char* dbgStr;
#endif // LL_DEBUG
} LinkedList;

#ifdef LL_DEBUG
char* ll_debug();
#endif // LL_DEBUG

// External methods
bool ll_push_front();
void* ll_pop_front();
bool ll_remove();
bool ll_free();
bool ll_at();
bool ll_find();
bool ll_sort();
bool ll_create( LinkedList** llist );
size_t ll_size();

#endif // LINKED_LIST_H
