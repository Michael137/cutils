#include <containers/hashmap.h>
#include <containers/linked_list.h>

#include <utils/ll_loop/ll_loop.h>

/*
 * Naive solution:
 * 1. Iterate over linked list
 * 2. Save pointer to each element encountered in hashmap
 * 3. On next element check if already encountered. If so,
 *    the linked list has a loop
 */
int ll_has_loop_naive( __attribute( ( unused ) ) LinkedList const* llist )
{
	return LL_FAILURE;
}
