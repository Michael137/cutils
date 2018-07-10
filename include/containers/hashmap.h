#ifndef HASHMAP_H_IN
#define HASHMAP_H_IN

#include <containers/linked_list.h>

#include <utils/debug.h> // debug_more_

// TODO: consolidate error handling mechanisms
// HashMap Constats
#define HM_FAILURE -1
#define HM_SUCCESS 1
#define HM_INVALID_ARGS 2

/*
 * TODO:
 *
 * CREATE: done
 * INSERT: done
 * SEARCH: done
 * KEY SEARCH
 * DELETE
 * ITERATOR
 * RESIZE
 */
typedef struct HashNode_ {

	void const* key;
	void const* value;

} HashNode_;

typedef struct HashMap_ {

	size_t size;
	size_t elements;

#if HM_DEBUG
	size_t collisions_;
	char* dbgStr;
#endif

	size_t ( *hash_fn )( void const* );
	bool ( *cmp_fn )( void const*, void const* );

	// Array of hash buckets of hash nodes
	LinkedList** buckets;

} HashMap;

int hm_create( HashMap** map, size_t ( *hash_fn )( void const* ),
			   bool ( *cmp_fn )( void const*, void const* ) );
int hm_create_str2int( HashMap** map );
int hm_create_str2str( HashMap** map );
int hm_create_int2int( HashMap** map );
int hm_create_int2str( HashMap** map );
int hm_create_ptr2ptr( HashMap** map );

void hm_free( HashMap* map );

// TODO: hm_insert with option to call set_node_type()
void hm_insert( HashMap** const map, void const* key, void const* value );
void hm_insert_typed( HashMap** const map, void const* key, void const* value );
void const* hm_get( HashMap const* map, void const* key );

void hm_print( HashMap const* const,
			   void ( *print_fn )( LinkedListNode_ const* ) );

size_t hm_debug_get_collisions( HashMap const* map );

// TODO: add bucket distribution info and average load factor
#define HM_DEBUG_LOG( map )                                                    \
	do {                                                                       \
		DEBUG_MORE_( HM_DEBUG, "%s (%ldE:%ldB:%ldC)\n",                        \
					 DBGSTR( HM_DEBUG, map ), map->elements, map->size,        \
					 DBG_CONTAINER_MEM( HM_DEBUG, map, collisions_, 0UL ) );   \
	} while( 0 )

#endif // HASHMAP_H_IN
