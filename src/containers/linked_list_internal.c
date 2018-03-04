#include <containers/linked_list_internal.h>
#include <stdio.h> // printf

void ll_debug_node_( LinkedListNode_ const* node, char const* extra )
{
#ifdef LL_DEBUG
	printf( "%s LinkedListNode_ Debug: %s\n", extra, node->dbgStr );
#endif // LL_DEBUG
}

bool void_ptrs_equal_( void const* lhs, void const* rhs,
					   VOID_PTR_TYPE_ type_tag )
{
	switch( type_tag ) {
	case INT:
		return *(int*)lhs == *(int*)rhs;
	case CSTRING:
		return *(char*)lhs == *(char*)rhs;
	}

	return false;
}
