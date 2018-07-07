#include <stddef.h> // size_t
#include <stdio.h>  // printf
#include <stdlib.h> // malloc
#include <string.h> // memcpy

#include <containers/linked_list.h>
#include <containers/linked_list_internal.h>

static void ll_inc_size_( LinkedList** llist ) { ( *llist )->size++; }

bool ll_create( LinkedList** llist )
{
	*llist = malloc( sizeof( LinkedList ) );
	if( *llist ) {
		( *llist )->head = NULL;
		( *llist )->tail = NULL;
		( *llist )->size = 0;

#if LL_DEBUG
		( *llist )->dbgStr = "Linked List Created";
#endif

		return LL_SUCCESS;
	} else
		return LL_FAILURE;
}

size_t ll_size( LinkedList const* llist ) { return llist->size; }

// TODO: _Generic?
bool ll_push_front( LinkedList** llist, void const* data,
					const size_t data_size )
{
	if( llist && *llist ) {
		void* copy = malloc( data_size );

		if( copy == NULL ) return LL_FAILURE;

		memcpy( copy, data, data_size );

		LinkedListNode_* node = malloc( sizeof( LinkedListNode_ ) );

		if( node ) {
			node->data = copy;
			node->type_tag_ = UNKNOWN;

#if LL_DEBUG
			node->dbgStr = "Node created";
#endif // LL_DEBUG

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

bool ll_free( LinkedList* llist )
{
	if( llist ) {
		LinkedListNode_* tmp = llist->head;
		while( tmp != NULL ) {
			// TODO: streamline LL_DEBUG_LOG so it can be uncommented
			// LL_DEBUG_NODE_LOG( tmp, "From free" );
			LinkedListNode_* next = tmp->next;
			free( tmp->data );
			free( tmp );
			tmp = next;
		}

		free( llist );
		llist = NULL;
	}

	return LL_SUCCESS;
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

				free( curr->data );
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
				// TODO: streamline LL_DEBUG_LOG so it can be uncommented
				// LL_DEBUG_NODE_LOG( tmp, "From Find internal" );

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
