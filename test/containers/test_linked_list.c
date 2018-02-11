#include <containers/linked_list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    printf( "~~~ Starting Linked List Tests ~~~\n" );

    LinkedList* llist;
    ll_create( &llist );

    ll_push_front( &llist, "String Node", 12 );
    ll_push_front( &llist, "String Node2", 13 );
    ll_push_front( &llist, "String Node3", 13 );
    int integer = 137;
    ll_push_front( &llist, &integer, sizeof( int ) );

    char* msg = strdup( "Allocated String Node" );
    ll_push_front( &llist, msg, strlen(msg) + 1 );
    free( msg );
    
    char* at_msg = ll_at( llist, 0 );
    puts( at_msg );

    int at_msg2 = *(int*)ll_at( llist, 1 );
    printf( "%d\n", at_msg2 );

    char* at_msg3 = ll_at( llist, 2 );
    puts( at_msg3 );

//    ll_remove( &llist, 0 );
//    ll_remove( &llist, 0 );
    ll_remove( &llist, 1 );
    char* at_msg4 = ll_at( llist, 0 );
    puts( at_msg4 );

    ll_free( &llist );

    return 0;
}
