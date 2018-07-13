#ifndef LINKED_LIST_H_IN
#define LINKED_LIST_H_IN

#include <containers/linked_list_internal.h>
#include <stdbool.h>	 // bool
#include <stddef.h>		 // size_t
#include <utils/debug.h> // debug_more_

// Linked List Constats
#define LL_FAILURE -1
#define LL_SUCCESS 1
#define LL_INVALID_ARGS 2

// Linked List Externals
typedef struct LinkedList_
{
	LinkedListNode_ *head, *tail;
	size_t size;
	void ( *dealloc_data_fn_ )( void* );

#if LL_DEBUG
	char* dbgStr;
#endif // LL_DEBUG
} LinkedList;

#define LL_DEBUG_LOG( llist )                                                  \
	do {                                                                       \
		DEBUG_MORE_( LL_DEBUG, "%s\n", DBGSTR( LL_DEBUG, llist ) );            \
	} while( 0 )

// External methods
bool ll_push_front( LinkedList**, void const*, const size_t );
bool ll_push_front_alloc( LinkedList**, void*, const size_t );
bool ll_pop_front( LinkedList** );
bool ll_remove( LinkedList**, const size_t );
bool ll_free( LinkedList* );
bool ll_free_custom( LinkedList*, void ( *fn )( void* ) );
void* ll_at( LinkedList const*, const size_t );
bool ll_create( LinkedList** );
size_t ll_size( LinkedList const* );
size_t ll_find_int( LinkedList const*, void const* );
size_t ll_find_string( LinkedList const*, void const* );
size_t ll_find( LinkedList const*, void const*,
				bool ( * )( void const*, void const* ) );
void ll_set_dealloc_fn( LinkedList** llist, void ( *fn )( void* ) );

#define LL_FOR_EACH_BEGIN( var, llist )                                        \
	LinkedListNode_* _tmp = ( llist )->head;                                   \
	size_t _ll_ctr = 0;                                                        \
	while( _tmp != NULL ) {                                                    \
		var = _tmp->data;

#define LL_FOR_EACH_END()                                                      \
	_tmp = _tmp->next;                                                         \
	_ll_ctr++;                                                                 \
	}

#endif // LINKED_LIST_H_IN

// TODO: implement alternative linked list with only macros as
// templating/codegen
