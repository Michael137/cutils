#include <containers/linked_list.h>
#include <stdio.h>

int main()
{
    printf( "~~~ Starting Linked List Tests ~~~\n" );

    LinkedList* llist;
    ll_create( &llist );

    ll_push_front( &llist, "Node 1", 7 );

    ll_debug( llist, "From test" );

    printf( "Size: %zd\n", ll_size( llist ) );

    ll_free( &llist );

    return 0;
}
