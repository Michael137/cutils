#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

#include <utils/ll_loop/ll_loop.h>

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
	ll_push_front( &llist, "Node5", 6 );
	ll_push_front( &llist, "Node4", 6 );
	ll_push_front( &llist, "Node3", 6 );
	ll_push_front( &llist, "Node2", 6 );
	ll_push_front( &llist, "Node1", 6 );
	ll_push_front( &llist, "Node0", 6 );

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
	char const* ret_msg2 = n2->data;
	char const* ret_msg5 = n5->next->data;
	size_t cmp_sz = strlen( at_msg5 );
	//assert( strncmp( ret_msg2, ret_msg5, strlen( ret_msg5 ) ) == 0 );
	assert( strncmp( ret_msg2, ret_msg5, cmp_sz ) == 0 );
	puts( "~~~> test_ll_loop: Linked list loop created..." );
	puts( "\t~~~> test_ll_loop: testing naive..." );
	assert( ll_has_loop_naive( llist ) );
	puts( "\t~~~> test_ll_loop: testing naive hashed..." );
	assert( ll_has_loop_naive_hashed( llist ) );

	// Remove loop
	puts( "~~~> test_ll_loop: Linked list loop removed..." );
	n5->next = NULL;
	assert( !ll_has_loop_naive( llist ) );
	assert( !ll_has_loop_naive_hashed( llist ) );

	// Cleanup
	ll_free( llist );

	return 0;
}
