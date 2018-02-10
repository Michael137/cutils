#include <containers/linked_list.h>
#include <stdio.h>

int main()
{
    printf( "~~~ Starting Linked List Tests ~~~\n" );

    LinkedList* llist;
    ll_create( &llist );

    ll_push_front( &llist, "Node 1", 7 );

    ll_debug( llist );

    printf( "Size: %zd\n", ll_size( llist ) );

    printf( "Node Debug: %s, Node Data: %s\n", llist->head->dbgStr, llist->head->data );

    return 0;
}
