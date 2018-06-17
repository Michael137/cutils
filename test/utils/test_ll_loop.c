#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

#include <utils/ll_loop/ll_loop.h>

// p-shaped:
//
//	   Node0-->Node1-->Node2-->Node3
//						 ^     |
//						 |     |
//						 |     v
//					  Node5<--Node4
//
// Circular:
//
//	   Node0-->Node1-->Node2-->Node3
//		^			            |
//		|			            |
//		|   		            v
//    Node7<--Node6<--Node5<--Node4

// Test defines
#define LIST_SZ 100
#define LOOP_OFFSET 10
#define BUF_SZ 21
#define BUF_MSG "Node%016d"
#define BUF_SPRINTF( buffer ) sprintf( buffer, BUF_MSG, i );

int main()
{
	puts( "~~~ Starting test_ll_loop ~~~" );

	// Construct linked list
	LinkedList* llist;
	ll_create( &llist );

	for( int i = 0; i < LIST_SZ; ++i ) {
		char buf[BUF_SZ];
		BUF_SPRINTF( buf );
		ll_push_front( &llist, buf, BUF_SZ );
	}

	char* collision_pt = ll_at( llist, LIST_SZ - LOOP_OFFSET );
	puts( collision_pt );

	char* last_pt = ll_at( llist, LIST_SZ - 1 );
	puts( last_pt );

	puts( "~~~> test_ll_loop: Linked list created..." );

	// Create loop
	LinkedListNode_* collision_node = NULL;
	assert( ll_get_node_( llist, LIST_SZ - LOOP_OFFSET, &collision_node ) ==
			LL_SUCCESS );

	LinkedListNode_* last_node = NULL;
	assert( ll_get_node_( llist, LIST_SZ - 1, &last_node ) == LL_SUCCESS );

	last_node->next = collision_node;
	char const* collision_data = collision_node->data;
	char const* last_data = last_node->next->data;
	assert( strncmp( collision_data, last_data, BUF_SZ ) == 0 );

	// Detect loop; Benchmark different methods
	puts( "~~~> test_ll_loop: Linked list loop created..." );
	puts( "\t~~~> test_ll_loop: testing naive..." );
	float start = (float)clock() / CLOCKS_PER_SEC;
	assert( ll_has_loop_naive( llist ) );
	float end = (float)clock() / CLOCKS_PER_SEC;
	printf( "\t\t~~~> %fs elapsed\n", end - start );

	puts( "\t~~~> test_ll_loop: testing naive hashed..." );
	start = (float)clock() / CLOCKS_PER_SEC;
	assert( ll_has_loop_naive_hashed( llist ) );
	end = (float)clock() / CLOCKS_PER_SEC;
	printf( "\t\t~~~> %fs elapsed\n", end - start );

	// Remove loop
	puts( "~~~> test_ll_loop: Linked list loop removed..." );
	last_node->next = NULL;
	assert( !ll_has_loop_naive( llist ) );
	assert( !ll_has_loop_naive_hashed( llist ) );

	// Cleanup
	ll_free( llist );

	return 0;
}
