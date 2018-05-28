#include <stdio.h>
#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

#include <assert.h>

// Node0-->Node1-->Node2-->Node3
//                   ^     |
//                   |     |
//                   |     v
//                Node5<--Node4

int main()
{
	puts( "~~~ Starting test_ll_loop ~~~" );

	// Construct linked list
	LinkedList* llist;
	ll_create( &llist );
	ll_push_front( &llist, "Node5", 5 );
	ll_push_front( &llist, "Node4", 5 );
	ll_push_front( &llist, "Node3", 5 );
	ll_push_front( &llist, "Node2", 5 );
	ll_push_front( &llist, "Node1", 5 );
	ll_push_front( &llist, "Node0", 5 );

	char* at_msg2 = ll_at( llist, 2 );
	puts( at_msg2 );

	char* at_msg5 = ll_at( llist, 5 );
	puts( at_msg5 );

	puts( "~~~> test_ll_loop: Linked list created..." );

	// Create loop
	LinkedListNode_* n2 = NULL;
	assert( ll_get_node_( llist, 2, &n2 ) == LL_SUCCESS );

	LinkedListNode_* n5 = NULL;
	assert( ll_get_node_( llist, 5, &n5 ) == LL_SUCCESS );

	n5->next = n2;
	assert( strcmp( n5->next->data, n2->data ) == 0 );
	puts( "~~~> test_ll_loop: Linked list loop created..." );

//	ll_print( &llist );

	// Cleanup
//	ll_free( &llist );

	return 0;
}
