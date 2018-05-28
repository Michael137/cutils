#include <stdio.h>
#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

// Node0-->Node1-->Node2-->Node3
//                   ^     |
//                   |     |
//                   |     v
//                Node5<--Node4

int main()
{
	// Construct linked list
	LinkedList* llist;
	ll_create( &llist );
	ll_push_front( &llist, "Node5", 5 );
	ll_push_front( &llist, "Node4", 5 );
	ll_push_front( &llist, "Node3", 5 );
	ll_push_front( &llist, "Node2", 5 );
	ll_push_front( &llist, "Node1", 5 );
	ll_push_front( &llist, "Node0", 5 );

//	// Create loop
//	LinkedListNode_* n5 = ll_get_node_( &llist, 5 );
//	LinkedListNode_* n2 = ll_get_node_( &llist, 2 );
//	n5->next = n2;

//	ll_print( &llist );

	// Cleanup
	ll_free( &llist );

	return 0;
}
