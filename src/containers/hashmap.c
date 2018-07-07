#include <stdio.h>
#include <stdlib.h>

#include <containers/hashmap.h>

static void hm_debug_collisions_incr( __attribute((unused)) HashMap** const map )
{
#if HM_DEBUG
	( *map )->collisions_++;
#endif
}

size_t hm_debug_get_collisions( __attribute((unused)) HashMap const* map )
{
#if HM_DEBUG
	return map->collisions_;
#else
	return 0;
#endif
}

static size_t const sc_hm_min_size_ = 128;

int hm_create( HashMap** map, size_t ( *hash_fn )( void const* ),
			   bool ( *cmp_fn )( void const*, void const* ) )
{
	*map = malloc( sizeof( HashMap ) + sc_hm_min_size_ * sizeof( LinkedList ) );
	if( map && *map ) {
		( *map )->size = sc_hm_min_size_;
		( *map )->hash_fn = hash_fn;
		( *map )->cmp_fn = cmp_fn;

#if HM_DEBUG
		( *map )->collisions_ = 0;
		( *map )->dbgStr = "HashMap created";
#endif

		size_t i = 0;
		for( ; i < sc_hm_min_size_; ++i ) {
			LinkedList* llist;
			ll_create( &llist );
			( *map )->buckets[i] = *llist;

			// TODO: map.buckets should be array of pointers
			//       then this free can be moved to hm_free()
			free( llist );
		}
		return HM_SUCCESS;
	} else {
		return HM_INVALID_ARGS;
	}

	return HM_FAILURE;
}

void hm_free( HashMap* map )
{
	// TODO: can be changed to ll_free()
	//       once buckets contains pointers
	size_t i = 0;
	for( ; i < map->size; ++i ) {
		LinkedListNode_* tmp = ( map->buckets[i] ).head;
		while( tmp != NULL ) {

			// TODO: streamline LL_DEBUG_LOG so it can be uncommented
			//#ifdef LL_DEBUG
			//			char msg[50];
			//			sprintf( msg, "From free hm_free at idx %ld", i );
			//			LL_DEBUG_NODE_LOG( tmp, msg );
			//#endif

			LinkedListNode_* next = tmp->next;
			free( tmp->data );
			free( tmp );
			tmp = next;
		}
	}
	free( map );
	map = NULL;
}

void hm_insert( HashMap** const map, void const* key, void const* value )
{
	size_t hsh = ( *map )->hash_fn( key );
	size_t idx = hsh % ( *map )->size;

	// TODO: error handling
	LinkedList* llist = &( ( *map )->buckets[idx] );

	if( llist->head != NULL ) {
		//		TODO: streamline LL_DEBUG_LOG so it can be uncommented
				// LL_DEBUG_LOG( llist );
		hm_debug_collisions_incr( map );
	}

	HashNode_* node = malloc( sizeof( HashNode_ ) );
	node->key = key;
	node->value = value;
	ll_push_front( &llist, node, sizeof( HashNode_ ) );
	free( node );
}

void const* hm_get( HashMap const* map, void const* key )
{
	size_t hsh = map->hash_fn( key );
	size_t idx = hsh % map->size;

	// TODO: implement ll_find with custom comparator
	LinkedList const* llist = &( map->buckets[idx] );
	LinkedListNode_ const* head = llist->head;

	while( head != NULL ) {
		HashNode_* node_data = head->data;
		if( map->cmp_fn( node_data->key, key ) ) return node_data->value;

		head = head->next;
	}

	return NULL;
}
