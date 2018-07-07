#ifndef LINKED_LIST_INTERNAL_H
#define LINKED_LIST_INTERNAL_H

#include <stdbool.h> // bool

#include <utils/debug.h> // debug_more_

typedef enum VOID_PTR_TYPE_ {

	UNKNOWN = -1,
	INT = 0,
	CSTRING

} VOID_PTR_TYPE_;

typedef struct LinkedListNode_ {

	VOID_PTR_TYPE_ type_tag_;
	struct LinkedListNode_* next;
	void* data;

#if LL_DEBUG == 1
	char* dbgStr;
#endif // LL_DEBUG

} LinkedListNode_;

#define ll_debug_node_( node )                                                 \
	do {                                                                       \
		debug_more_( LL_DEBUG, "%s\n", DBGSTR( LL_DEBUG, node ) );             \
	} while( 0 )

bool void_ptrs_equal_( void const* lhs, void const* rhs,
					   VOID_PTR_TYPE_ type_tag );

#define LL_GEN_FIND_CMP_FN_( name, t )                                         \
	static bool name##_cmp_fn_( void const* arg1, void const* arg2 )           \
	{                                                                          \
		return void_ptrs_equal_( arg1, arg2, t );                              \
	}

#endif // LINKED_LIST_INTERNAL_H
