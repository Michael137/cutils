#include <containers/linked_list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf( "~~~ Starting Linked List Tests ~~~\n" );

    LinkedList* llist;
    ll_create( &llist );

    ll_push_front( &llist, "String Node", sizeof( char ) );
    ll_push_front( &llist, "Int Node", sizeof( int ) );

    char* msg = strdup( "Allocated String Node" );
    ll_push_front( &llist, msg, sizeof( *msg ) );
    free( msg );

    ll_debug( llist, "From test" );
    ll_free( &llist );

    return 0;
}
