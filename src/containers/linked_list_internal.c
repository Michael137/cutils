#include <containers/linked_list_internal.h>
#include <stdio.h> // printf

void ll_debug_node_( LinkedListNode_ const* node, char const* extra ) 
{
#ifdef LL_DEBUG
    printf( "%s LinkedListNode_ Debug: %s\n", extra, node->dbgStr );
#endif // LL_DEBUG
}
