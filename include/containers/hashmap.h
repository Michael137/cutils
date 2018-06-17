#ifndef HASHMAP_H_IN
#define HASHMAP_H_IN

#include <containers/linked_list.h>

// TODO: consolidate error handling mechanisms
// HashMap Constats
#define HM_FAILURE -1
#define HM_SUCCESS 1
#define HM_INVALID_ARGS 2

/*
 * TODO:
 *
 * struct HashMap
 *
 * CREATE
 * INSERT
 * SEARCH
 * DELETE
 */
typedef struct HashNode_ {

	void const* key;
	void const* value;

} HashNode_;

typedef struct HashMap_ {

	size_t size;

#ifdef HM_DEBUG
	size_t collisions_;
	char* dbgStr;
#endif

	size_t ( *hash_fn )( void const* );
	bool ( *cmp_fn )( void const*, void const* );

	// Array of hash buckets of hash nodes
	LinkedList buckets[];

} HashMap;

int hm_create( HashMap** map, size_t ( *hash_fn )( void const* ),
			   bool ( *cmp_fn )( void const*, void const* ) );
void hm_free( HashMap* map );
void hm_insert( HashMap** const map, void const* key, void const* value );
void const* hm_get( HashMap const* map, void const* key );

#ifdef HM_DEBUG
void hm_debug( HashMap const*, char const* );
size_t hm_debug_get_collisions( HashMap const* map );
#else
inline void hm_debug() {}
inline size_t hm_debug_get_collisions() {}
#endif // HM_DEBUG

#endif // HASHMAP_H_IN
