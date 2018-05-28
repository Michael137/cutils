#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

#include <stdio.h>

int ll_get_node_( LinkedList const* llist, size_t idx, LinkedListNode_** node )
{
	LinkedListNode_* tmp = llist->head;
	int ctr = 0;
	while( ctr++ < idx && tmp != NULL )
	{
		ll_debug_node_( tmp, "From ll_get_node_" );
		tmp = tmp->next;
	}

	if( ctr == idx + 1 )
		*node = tmp;
	else
		return LL_FAILURE;

	return LL_SUCCESS;
}

void ll_print( LinkedList const* llist )
{
}
