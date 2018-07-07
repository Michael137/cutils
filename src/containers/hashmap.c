#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>

static void hm_debug_collisions_incr( __attribute( ( unused ) )
									  HashMap** const map )
{
#if HM_DEBUG
	( *map )->collisions_++;
#endif
}

size_t hm_debug_get_collisions( __attribute( ( unused ) ) HashMap const* map )
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

// djb hash
static size_t default_hash_str_( void const* key )
{
	size_t hash = 5381;
	char const* str = (char const*)key;
	int c;

	while( ( c = *str++ ) )
		hash = ( ( hash << 5 ) + hash ) + c; /* hash * 33 + c */

	return hash;
}

static bool default_cmp_str_( void const* key, void const* value )
{
	return strcmp( (char*)key, (char*)value ) == 0;
}

static size_t default_hash_int_( void const* num )
{
	size_t key = *(int*)num;
	key = ( ~key ) + ( key << 21 ); // key = (key << 21) - key - 1;
	key = key ^ ( key >> 24 );
	key = ( key + ( key << 3 ) ) + ( key << 8 ); // key * 265
	key = key ^ ( key >> 14 );
	key = ( key + ( key << 2 ) ) + ( key << 4 ); // key * 21
	key = key ^ ( key >> 28 );
	key = key + ( key << 31 );
	return key;
}

static bool default_cmp_int_( void const* key, void const* value )
{
	return *(int*)key == *(int*)value;
}

int hm_create_str2int( HashMap** map )
{
	return hm_create( map, default_hash_str_, default_cmp_int_ );
}

int hm_create_str2str( HashMap** map )
{
	return hm_create( map, default_hash_str_, default_cmp_str_ );
}

int hm_create_int2int( HashMap** map )
{
	return hm_create( map, default_hash_int_, default_cmp_int_ );
}

int hm_create_int2str( HashMap** map )
{
	return hm_create( map, default_hash_int_, default_cmp_str_ );
}
