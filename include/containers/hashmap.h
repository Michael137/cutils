#ifndef HASHMAP_H_IN
#define HASHMAP_H_IN

#include <containers/linked_list.h>

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
	void* value;
} HashNode;

typedef struct HashMap_ {

	// Array of hash buckets of hash nodes
	LinkedList** llist;
} HashMap;


int hm_create( HashMap** map );
void hm_insert( HashMap** map, void const* key, void const* value );

#endif // HASHMAP_H_IN
