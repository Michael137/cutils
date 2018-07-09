#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>
#include <containers/linked_list_helpers.h>
#include <core/hash.h>

static size_t const sc_hm_min_size_ = 4096;

// Forward declares for statics
static void hm_rebalance_( HashMap** const map, size_t new_size );
static void hm_insert_( HashMap** const map, void const* key, void const* value,
						bool rebalancing );
static void hm_debug_collisions_incr( __attribute( ( unused ) )
									  HashMap** const map );
static int hm_create_( HashMap** map, size_t ( *hash_fn )( void const* ),
					   bool ( *cmp_fn )( void const*, void const* ),
					   size_t size );
static size_t default_hash_str_( void const* key );
static bool default_cmp_str_( void const* key, void const* value );
static size_t default_hash_int_( void const* num );
static size_t default_hash_ptr_( void const* num );
static bool default_cmp_int_( void const* key, void const* value );
static bool default_cmp_ptr_( void const* key, void const* value );

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

static int hm_create_( HashMap** map, size_t ( *hash_fn )( void const* ),
					   bool ( *cmp_fn )( void const*, void const* ),
					   size_t size )
{
	*map = malloc( sizeof( HashMap ) + size * sizeof( LinkedList ) );
	if( map && *map ) {
		( *map )->size = size;
		( *map )->hash_fn = hash_fn;
		( *map )->cmp_fn = cmp_fn;
		( *map )->elements = 0;

#if HM_DEBUG
		( *map )->collisions_ = 0;
		( *map )->dbgStr = "HashMap created";
#endif

		size_t i = 0;
		for( ; i < size; ++i ) {
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

int hm_create( HashMap** map, size_t ( *hash_fn )( void const* ),
			   bool ( *cmp_fn )( void const*, void const* ) )
{
	return hm_create_( map, hash_fn, cmp_fn, sc_hm_min_size_ );
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

static void hm_insert_( HashMap** const map, void const* key, void const* value,
						bool rebalancing )
{
	// TODO: profile
	if( !rebalancing && ( *map )->elements >= 1.5 * ( *map )->size ) {
		hm_rebalance_( map, ( *map )->elements * 2.5 );
	}
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

	( *map )->elements++;
}

static void hm_rebalance_( HashMap** const map, size_t new_size )
{
	HashMap* tmp;
	hm_create_( &tmp, NULL, NULL, new_size );
	tmp->hash_fn = ( *map )->hash_fn;
	tmp->cmp_fn = ( *map )->cmp_fn;
	size_t i = 0;
	for( ; i < ( *map )->size; ++i ) {
		LinkedList llist = ( *map )->buckets[i];
		LinkedListNode_* node = llist.head;
		while( node != NULL ) {
			hm_insert_( &tmp, ( (HashNode_*)node->data )->key,
						( (HashNode_*)node->data )->value, true );
			node = node->next;
		}
	}

	hm_free( *map );
	*map = tmp;
}

void hm_insert( HashMap** const map, void const* key, void const* value )
{
	hm_insert_( map, key, value, false );
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

static size_t default_hash_str_( void const* key )
{
	return hash_str_djb( (char const*)key );
}

static bool default_cmp_str_( void const* key, void const* value )
{
	return strcmp( (char*)key, (char*)value ) == 0;
}

static size_t default_hash_int_( void const* key )
{
	return hash_int_32( *(uint32_t*)key );
}

static size_t default_hash_ptr_( void const* key )
{
	return hash_int_64( (uintptr_t)key );
}

static bool default_cmp_int_( void const* key, void const* value )
{
	return *(int*)key == *(int*)value;
}

static bool default_cmp_ptr_( void const* key, void const* value )
{
	return (uintptr_t)key == (uintptr_t)value;
}

int hm_create_str2int( HashMap** map )
{
	return hm_create( map, default_hash_str_, default_cmp_str_ );
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
	return hm_create( map, default_hash_int_, default_cmp_int_ );
}

int hm_create_ptr2ptr( HashMap** map )
{
	return hm_create( map, default_hash_ptr_, default_cmp_ptr_ );
}

void hm_print( HashMap const* const map,
			   void ( *print_fn )( LinkedListNode_ const* node ) )
{
	LinkedList const* llist = NULL;
	size_t i = 0;
	for( ; i < map->size; ++i ) {
		llist = &( map->buckets[i] );
		if( llist->size != 0 ) {
			printf( "Bucket %ld\n", i );
			if( print_fn != NULL )
				ll_print_custom( llist, print_fn );
			else
				ll_print( llist );
		}
	}
}
