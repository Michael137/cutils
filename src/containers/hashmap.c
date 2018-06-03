#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>

static size_t const sc_hm_min_size_ = 128;

int hm_create( HashMap** map ) {
	*map = malloc( sizeof( HashMap ) + sc_hm_min_size_ * sizeof( LinkedList ) );
	if( map && *map )
	{
		(*map)->size = sc_hm_min_size_;

		size_t i = 0;
		for( ; i < sc_hm_min_size_; ++i)
		{
			LinkedList* llist;
			ll_create( &llist );
			(*map)->buckets[i] = *llist;

			// TODO: map.buckets should be array of pointers
			//       then this free can be moved to hm_free()
			free( llist );
		}
		return HM_SUCCESS;
	}
	else
	{
		return HM_INVALID_ARGS;
	}

	return HM_FAILURE;
}

void hm_free( HashMap* map )
{
	// TODO: can be changed to ll_free()
	//       once buckets contains pointers
	size_t i = 0;
	for( ; i < map->size; ++i )
	{
		LinkedListNode_* tmp = (map->buckets[i]).head;
		while( tmp != NULL ) {
			char msg[50];
			sprintf( msg, "From free hm_free at idx %ld", i );
			ll_debug_node_( tmp, msg );
			LinkedListNode_* next = tmp->next;
			free( tmp->data );
			free( tmp );
			tmp = next;
		}
	}
	free( map );
	map = NULL;
}

// TODO: replace with user-defined hash function
static size_t hash_str( char const* str )
{
	size_t hash = 5381;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

void hm_insert( HashMap** map, void const* key, void const* value )
{
	size_t hsh = hash_str(key);
	size_t idx = hsh % (*map)->size;

	// TODO: error handling
	LinkedList* llist = &((*map)->buckets[idx]);
	HashNode_* node = malloc( sizeof( HashNode_ ) );
	node->key = key;
	node->value = value;
	ll_push_front( &llist, node, sizeof( HashNode_ ) );
	free( node );
}

void const * hm_get( HashMap const* map, void const* key )
{
	size_t hsh = hash_str(key);
	size_t idx = hsh % map->size;

	// TODO: implement ll_find with custom comparator
	LinkedList const* llist = &(map->buckets[idx]);
	LinkedListNode_ const* head = llist->head;

	while( head != NULL )
	{
		HashNode_* node_data = head->data;
		if( strcmp( (char*)node_data->key, (char*) key ) == 0 )
			return node_data->value;

		head = head->next;
	}

	//return ll_at( &(map->buckets[idx]), 0 );
	return NULL;
}
