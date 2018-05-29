#include <stdio.h>
#include <stdlib.h>

#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

static void ll_print_node_data_( LinkedListNode_ const* node )
{
	void* tmp = NULL;
	switch( node->type_tag_ ) {
	case UNKNOWN:
		printf( ">> \tdata: (unknown)\n" );
		break;
	case INT:
		tmp = node->data;
		printf( ">> \tdata: %d\n", tmp );
		break;
	case CSTRING:
		tmp = node->data;
		printf( ">> \tdata: %s\n", tmp );
		break;
	}
}

static void ll_print_node_( LinkedListNode_ const* node )
{
	ll_print_node_data_( node );
#ifdef LL_DEBUG
	printf( ">> \tdbgStr: %s\n", node->dbgStr );
#endif
}

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
	if( llist )
	{
		LinkedListNode_* tmp = llist->head;
		printf( ">> size: %d\n", llist->size );

		int ctr = 0;
		while( tmp != NULL )
		{
			printf( ">> \tid: %d\n>> \t>---------\n", ctr );
			ll_print_node_( tmp );
			printf( ">> \t---------<\n" );
			tmp = tmp->next;
			++ctr;
		}
	}
}

// TODO: implement
int ll_replace_node_( LinkedList** llist, size_t idx, LinkedListNode_* node ) { return 0; };

int ll_node_set_type( LinkedList** llist, size_t idx, VOID_PTR_TYPE_ type_tag )
{
	int ret = LL_FAILURE;
	LinkedListNode_* node = NULL;

	if( (ret = ll_get_node_( *llist, idx, &node )) == LL_SUCCESS )
	{
		node->type_tag_ = type_tag;
		ll_replace_node_( llist, idx, node );
	}

	return ret;
}
