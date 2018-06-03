#ifndef LINKED_LIST_INTERNAL_H
#define LINKED_LIST_INTERNAL_H

#include <stdbool.h> // bool

typedef enum VOID_PTR_TYPE_ {

	UNKNOWN = -1,
	INT = 0,
	CSTRING

} VOID_PTR_TYPE_;

typedef struct LinkedListNode_ {

	VOID_PTR_TYPE_ type_tag_;
	struct LinkedListNode_* next;
	void* data;

#ifdef LL_DEBUG
	char* dbgStr;
#endif // LL_DEBUG

} LinkedListNode_;

#ifdef LL_DEBUG
void ll_debug_node_( LinkedListNode_ const*, char const* );
#else
inline void ll_debug_node_() {}
#endif // LL_DEBUG

bool void_ptrs_equal_( void const* lhs, void const* rhs,
					   VOID_PTR_TYPE_ type_tag );

#define LL_GEN_FIND_CMP_FN_( name, t )                                         \
	static bool name##_cmp_fn_( void const* arg1, void const* arg2 )           \
	{                                                                          \
		return void_ptrs_equal_( arg1, arg2, t );                              \
	}

#endif // LINKED_LIST_INTERNAL_H
