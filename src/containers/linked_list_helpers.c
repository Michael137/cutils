#include <stdio.h>
#include <stdlib.h>

#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

static void ll_print_node_data_( LinkedListNode_ const* node )
{
	printf( "\ttype: %d\n", node->type_tag_ );
	switch( node->type_tag_ ) {
	case UNKNOWN:
		printf( ">> \tdata: (unknown)\n" );
		break;
	case INT:
		printf( ">> \tdata: %d\n", *(int*)node->data );
		break;
	case CSTRING:
		printf( ">> \tdata: %s\n", (char*)node->data );
		break;
	}
}

static void ll_print_node_( LinkedListNode_ const* node )
{
	ll_print_node_data_( node );
#if LL_DEBUG
	printf( ">> \tdbgStr: %s\n", node->dbgStr );
#endif
}

int ll_get_node_( LinkedList const* llist, size_t idx, LinkedListNode_** node )
{
	LinkedListNode_* tmp = llist->head;
	size_t ctr = 0;
	while( ctr++ < idx && tmp != NULL ) {
		tmp = tmp->next;
	}

	if( ctr == idx + 1 )
		*node = tmp;
	else
		return LL_FAILURE;

	return LL_SUCCESS;
}

void ll_print_custom( LinkedList const* llist, void (*print_fn)( LinkedListNode_ const* node ) )
{
	if( llist ) {
		LinkedListNode_* tmp = llist->head;
		printf( ">> size: %zd\n", llist->size );

		size_t ctr = 0;
		while( tmp != NULL ) {
			printf( ">> \t>---------\n>> \tid: %zd\n>>", ctr );
			print_fn( tmp );
			printf( ">> \t---------<\n" );
			tmp = tmp->next;
			++ctr;
		}
	}
}

void ll_print( LinkedList const* llist )
{
	ll_print_custom( llist, ll_print_node_ );
}

int ll_node_set_type( LinkedList** llist, size_t idx, VOID_PTR_TYPE_ type_tag )
{
	// TODO: refactor to use ll_get_node_()
	LinkedListNode_* tmp = ( *llist )->head;
	size_t ctr = 0;
	while( ctr++ < idx && tmp != NULL )
		tmp = tmp->next;

	if( ctr == idx + 1 )
		tmp->type_tag_ = type_tag;
	else
		return LL_FAILURE;

	return LL_SUCCESS;
}
