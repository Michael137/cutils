#include <containers/linked_list.h>
#include <stdio.h>

int main()
{
    LinkedList* llist;
    ll_create( &llist );

    printf( "Debug %s\n", llist->dbgStr );

    return 0;
}
