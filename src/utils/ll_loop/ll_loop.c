#include <stdio.h>
#include <string.h>

// TODO: remove hashmap.h dep.?
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
