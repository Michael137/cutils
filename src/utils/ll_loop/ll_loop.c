#include <inttypes.h>
#include <stdint.h>

#include <stdio.h>

#include <containers/hashmap.h>
#include <containers/linked_list.h>

#include <utils/ll_loop/ll_loop.h>

bool ll_has_loop_naive( LinkedList const* llist )
{
	size_t ptrs[llist->size];
	size_t i = 0;
	for( ; i < sizeof( ptrs ) / sizeof( ptrs[0] ); ++i )
		ptrs[i] = 0;

	LinkedListNode_* head = llist->head;
	while( head != NULL ) {
		size_t ptr = (size_t)head;
		size_t j = 0;
		for( ; j < sizeof( ptrs ) / sizeof( ptrs[0] ); ++j ) {
			if( ptrs[j] == ptr )
				return true;
			else if( ptrs[j] == 0 ) {
				ptrs[j] = ptr;
				break;
			}
		}

		head = head->next;
	}

	return false;
}

/*
 * TODO: create hash_map_int() and hash_map_str()
 *       with default hash/cmp fns
 */
static size_t hash_fn( void const* num )
{
	size_t key = ( ( size_t )(uintptr_t)num );
	key = ( ~key ) + ( key << 21 ); // key = (key << 21) - key - 1;
	key = key ^ ( key >> 24 );
	key = ( key + ( key << 3 ) ) + ( key << 8 ); // key * 265
	key = key ^ ( key >> 14 );
	key = ( key + ( key << 2 ) ) + ( key << 4 ); // key * 21
	key = key ^ ( key >> 28 );
	key = key + ( key << 31 );
	return key;
}

static bool cmp_fn( void const* key, void const* value )
{
	return (uintptr_t)key == (uintptr_t)value;
}

bool ll_has_loop_naive_hashed( LinkedList const* llist )
{
	bool found = false;
	HashMap* map;
	hm_create( &map, hash_fn, cmp_fn );

	LinkedListNode_* head = llist->head;
	while( head != NULL ) {
		void* ptr = (void*)(uintptr_t)head;
		uintptr_t cached = (uintptr_t)hm_get( map, ptr );
		if( !cached ) {
			hm_insert( &map, ptr, ptr );
			// TODO: streamline LL_DEBUG_LOG so it can be uncommented
			// LL_DEBUG_NODE_LOG( head, "From loop_naive_hashed *inserting*" );
		} else if( cached == (uintptr_t)ptr ) {
			LL_DEBUG_NODE_LOG( head );
			found = true;
			break;
		}

		head = head->next;
	}

	HM_DEBUG_LOG( map );
	hm_free( map );

	return found;
}
