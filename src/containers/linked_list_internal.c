#include <containers/linked_list_internal.h>
#include <string.h> // strcmp
#include <stdio.h> // printf

#ifdef LL_DEBUG
void ll_debug_node_( LinkedListNode_ const* node, char const* extra )
{
	printf( "%s LinkedListNode_ Debug: %s\n", extra, node->dbgStr );
}
#endif // LL_DEBUG

bool void_ptrs_equal_( void const* lhs, void const* rhs,
					   VOID_PTR_TYPE_ type_tag )
{
	switch( type_tag ) {
	case UNKNOWN:
		return false;
	case INT:
		return *(int*)lhs == *(int*)rhs;
	case CSTRING:
		return strcmp( (char*)lhs, (char*)rhs ) == 0;
	}

	return false;
}
