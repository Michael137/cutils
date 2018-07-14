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

bool ll_has_loop_naive_hashed( LinkedList const* llist )
{
	bool found = false;
	HashMap* map;
	hm_create_ptr( &map );

	LinkedListNode_* head = llist->head;
	while( head != NULL ) {
		// TODO: store address value in map properly
		void* ptr = (void*)(uintptr_t)head;
		uintptr_t cached = (uintptr_t)hm_get( map, ptr );
		if( !cached ) {
			hm_insert( &map, ptr, ptr );
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
