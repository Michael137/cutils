#include <stdio.h>
#include <containers/linked_list.h>

int main()
{
	LinkedList* llist;
	ll_create( &llist );

	ll_push_front( &llist, "String Node", 12 );
	ll_push_front( &llist, "String Node2", 13 );
	ll_push_front( &llist, "String Node3", 13 );

	char* at_msg = ll_at( llist, 0 );
	puts( at_msg );

	ll_free( &llist );

	return 0;
}
