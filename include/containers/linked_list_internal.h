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

void ll_debug_node_( LinkedListNode_ const*, char const* );

bool void_ptrs_equal_( void const* lhs, void const* rhs,
					   VOID_PTR_TYPE_ type_tag );


#endif // LINKED_LIST_INTERNAL_H
