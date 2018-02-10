#include <containers/linked_list.h>
#include <containers/linked_list_internal.h>
#include <stdlib.h>

bool ll_create( LinkedList** llist )
{
    *llist = malloc(sizeof(LinkedList));
    (*llist)->head = NULL;
    (*llist)->tail = NULL;
    (*llist)->size = 0;

#ifdef LL_DEBUG
    (*llist)->dbgStr = "Map Created";
#endif
}
