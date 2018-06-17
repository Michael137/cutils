#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

#include <utils/ll_loop/ll_loop.h>

// Node0-->Node1-->Node2-->Node3
//                   ^     |
//                   |     |
//                   |     v
//                Node5<--Node4

// Test defines
#define LIST_SZ 1500
#define LOOP_OFFSET 128
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

	char* at_msg2 = ll_at( llist, LIST_SZ - LOOP_OFFSET );
	puts( at_msg2 );

	char* at_msg5 = ll_at( llist, LIST_SZ - 1 );
	puts( at_msg5 );

	puts( "~~~> test_ll_loop: Linked list created..." );

	// Create loop
	LinkedListNode_* n2 = NULL;
	assert( ll_get_node_( llist, LIST_SZ - LOOP_OFFSET, &n2 ) == LL_SUCCESS );

	LinkedListNode_* n5 = NULL;
	assert( ll_get_node_( llist, LIST_SZ - 1, &n5 ) == LL_SUCCESS );

	n5->next = n2;
	char const* ret_msg2 = n2->data;
	char const* ret_msg5 = n5->next->data;
	assert( strncmp( ret_msg2, ret_msg5, strlen( ret_msg5 ) ) == 0 );

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
	n5->next = NULL;
	assert( !ll_has_loop_naive( llist ) );
	assert( !ll_has_loop_naive_hashed( llist ) );

	// Cleanup
	ll_free( llist );

	return 0;
}
