#ifndef LINKED_LIST_HELPERS_H
#define LINKED_LIST_HELPERS_H

#include <containers/linked_list.h>
#include <containers/linked_list_internal.h>

int ll_get_node_( LinkedList const*, size_t, LinkedListNode_** );
void ll_print( LinkedList const* );
int ll_node_set_type( LinkedList**, size_t, VOID_PTR_TYPE_ );
int ll_has_loop_naive( LinkedList const* llist );

#endif // LINKED_LIST_HELPERS_H
