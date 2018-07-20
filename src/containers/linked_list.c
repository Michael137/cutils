#include <containers/linked_list.h>
#include <containers/linked_list_internal.h>
#include <stddef.h> // size_t
#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <string.h> // memcpy

static void ll_inc_size_( LinkedList** llist ) { ( *llist )->size++; }

static void default_dealloc_fn_( void* data )
{
	free( data );
	data = NULL;
}

void ll_set_dealloc_fn( LinkedList** llist, void ( *fn )( void* ) )
{
	( *llist )->dealloc_data_fn_ = fn;
}

bool ll_create( LinkedList** llist )
{
	*llist = malloc( sizeof( LinkedList ) );
	if( *llist ) {
		( *llist )->head = NULL;
		( *llist )->tail = NULL;
		( *llist )->size = 0;
		( *llist )->dealloc_data_fn_ = default_dealloc_fn_;

		LL_SET_DBGSTR( ( *llist ), "Linked List Created" );

		return LL_SUCCESS;
	} else
		return LL_FAILURE;
}

size_t ll_size( LinkedList const* llist ) { return llist->size; }

// TODO: _Generic?
static bool ll_push_front_( LinkedList** llist, void const* data,
							const size_t data_size, bool allocated )
{
	if( llist && *llist ) {
		void* copy;
		if( allocated ) {
			copy = (void*)data;
		} else {
			copy = malloc( data_size );
			if( copy == NULL ) return LL_FAILURE;
			memcpy( copy, data, data_size );
		}

		LinkedListNode_* node = malloc( sizeof( LinkedListNode_ ) );

		if( node ) {
			node->data = copy;
			node->type_tag_ = UNKNOWN;

			LL_SET_DBGSTR( node, "Node Created" );

			LinkedListNode_* tmp = ( *llist )->head;
			node->next = tmp;

			( *llist )->head = node;

			ll_inc_size_( llist );

			return LL_SUCCESS;
		} else
			return LL_FAILURE;
	} else
		return LL_INVALID_ARGS;
}

bool ll_push_front_alloc( LinkedList** llist, void* data,
						  const size_t data_size )
{
	return ll_push_front_( llist, data, data_size, true );
}

bool ll_push_front( LinkedList** llist, void const* data,
					const size_t data_size )
{
	return ll_push_front_( llist, data, data_size, false );
}

static bool ll_free_( LinkedList* llist, void ( *dealloc_fn )( void* ) )
{
	if( llist ) {
		LinkedListNode_* tmp = llist->head;
		while( tmp != NULL ) {
			LinkedListNode_* next = tmp->next;
			dealloc_fn( tmp->data );
			free( tmp );
			tmp = next;
		}

		free( llist );
		llist = NULL;
	}

	return LL_SUCCESS;
}

bool ll_free_custom( LinkedList* llist, void ( *dealloc_fn )( void* ) )
{
	return ll_free_( llist, dealloc_fn );
}

bool ll_free( LinkedList* llist )
{
	return ll_free_( llist, llist->dealloc_data_fn_ );
}

void* ll_at( LinkedList const* llist, const size_t idx )
{
	if( llist != NULL ) {
		LinkedListNode_* tmp = llist->head;

		size_t ctr = 0;
		while( tmp != NULL ) {
			if( ctr == idx ) {
				LL_DEBUG_NODE_LOG( tmp );

				return (void*)tmp->data;
			}

			tmp = tmp->next;
			ctr++;
		}
	}
	return NULL;
}

bool ll_remove( LinkedList** llist, const size_t idx )
{
	if( llist && *llist ) {
		// TODO: llist_iter?
		LinkedListNode_ *curr = ( *llist )->head, *prev = NULL;

		size_t ctr = 0;
		while( curr ) {
			if( ctr == idx ) {
				if( prev == NULL )
					( *llist )->head = curr->next;
				else
					prev->next = curr->next;

				// FIXME: Allow dealloc fn as arg
				( *llist )->dealloc_data_fn_( curr->data );
				free( curr );
				( *llist )->size--;

				return LL_SUCCESS;
			}

			prev = curr;
			curr = curr->next;
			ctr++;
		}
	} else
		return LL_INVALID_ARGS;

	return LL_FAILURE;
}

bool ll_pop_front( LinkedList** llist )
{
	if( llist && *llist )
		return ll_remove( llist, 0 );
	else
		return LL_INVALID_ARGS;
}

size_t ll_find( LinkedList const* llist, void const* value,
				bool ( *cmp_fn )( void const*, void const* ) )
{
	if( llist != NULL ) {
		LinkedListNode_* tmp = llist->head;

		size_t ctr = 0;
		while( tmp != NULL ) {
			if( cmp_fn( value, tmp->data ) ) {
				LL_DEBUG_NODE_LOG( tmp );

				return ctr;
			}

			tmp = tmp->next;
			ctr++;
		}
	}
	return LL_FAILURE;
}

LL_GEN_FIND_CMP_FN_( int, INT )
LL_GEN_FIND_CMP_FN_( str, CSTRING )

size_t ll_find_int( LinkedList const* llist, void const* value )
{
	return ll_find( llist, value, int_cmp_fn_ );
}

size_t ll_find_string( LinkedList const* llist, void const* value )
{
	return ll_find( llist, value, str_cmp_fn_ );
}
