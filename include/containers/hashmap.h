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

	/*
 	 * hashFn*
 	 * cmpFn*
 	 */
} HashNode_;

typedef struct HashMap_ {

	size_t size;

	// Array of hash buckets of hash nodes
	LinkedList buckets[];
} HashMap;


int hm_create( HashMap** map );
void hm_free( HashMap** map );
void hm_insert( HashMap** map, void const* key, void const* value );
void const* hm_get( HashMap const* map, void const* key );

#endif // HASHMAP_H_IN
