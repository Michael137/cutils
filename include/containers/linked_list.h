#ifndef LINKED_LIST_H_IN
#define LINKED_LIST_H_IN

#include <containers/linked_list_internal.h>
#include <utils/debug.h> // debug_more_

#include <stdbool.h> // bool
#include <stddef.h>  // size_t

// Linked List Constats
#define LL_FAILURE -1
#define LL_SUCCESS 1
#define LL_INVALID_ARGS 2

// Linked List Externals
typedef struct LinkedList_ {
	LinkedListNode_ *head, *tail;
	size_t size;

#if LL_DEBUG == 1
	char* dbgStr;
#endif // LL_DEBUG
} LinkedList;

#define ll_debug( llist )                                                      \
	do {                                                                       \
		debug_more_( LL_DEBUG, "%s\n", DBGSTR( LL_DEBUG, llist ) );            \
	} while( 0 )

// External methods
bool ll_push_front( LinkedList**, void const*, const size_t );
bool ll_pop_front( LinkedList** );
bool ll_remove( LinkedList**, const size_t );
bool ll_free( LinkedList* );
void* ll_at( LinkedList const*, const size_t );
bool ll_create( LinkedList** );
size_t ll_size( LinkedList const* );
size_t ll_find_int( LinkedList const*, void const* );
size_t ll_find_string( LinkedList const*, void const* );
size_t ll_find( LinkedList const*, void const*,
				bool ( * )( void const*, void const* ) );

#endif // LINKED_LIST_H_IN

// TODO: implement alternative linked list with only macros as
// templating/codegen
