#ifndef LINKED_LIST_H
#define LINKED_LIST_H

// Linked List Externals
typedef struct LinkedList;

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
bool ll_create();
size_t ll_size();

#endif // LINKED_LIST_H
