#include <containers/hashmap.h>
#include <containers/linked_list_helpers.h>
#include <core/hash.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t const sc_hm_min_size_ = 16;

// Forward declares for statics
static void hm_rebalance_( HashMap** const map, size_t new_size );
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
	*map = malloc( sizeof( HashMap ) );
	if( map && *map ) {
		( *map )->size = size;
		( *map )->hash_fn = hash_fn;
		( *map )->cmp_fn = cmp_fn;
		( *map )->elements = 0;
		( *map )->dealloc_fn = NULL;

#if HM_DEBUG
		( *map )->collisions_ = 0;
		( *map )->dbgStr = "HashMap created";
#endif
		( *map )->buckets = malloc( sizeof( LinkedList ) * size );
		if( ( *map )->buckets == NULL ) {
			free( *map );
			*map = NULL;
			return HM_FAILURE;
		}

		size_t i = 0;
		for( ; i < size; ++i ) {
			LinkedList* llist;
			ll_create( &llist );
			( *map )->buckets[i] = llist;
		}
		return HM_SUCCESS;
	}

	*map = NULL;

	return HM_FAILURE;
}

int hm_create( HashMap** map, size_t ( *hash_fn )( void const* ),
			   bool ( *cmp_fn )( void const*, void const* ) )
{
	return hm_create_( map, hash_fn, cmp_fn, sc_hm_min_size_ );
}

static void hm_free_( HashMap* map, void ( *node_dealloc_fn )( void* ) )
{
	size_t i = 0;
	for( ; i < map->size; ++i ) {
		ll_free_custom( map->buckets[i], node_dealloc_fn );
		map->buckets[i] = NULL;
	}
	free( map->buckets );

	map->buckets = NULL;
	free( map );
	map = NULL;
}

void hm_free_custom( HashMap* map, void ( *node_dealloc_fn )( void* ) )
{
	hm_free_( map, node_dealloc_fn );
}

// TODO: remove code rep. from default ll dealloc
//       and find cleaner dealloc injection point for
//       hm_
static void default_node_dealloc_fn( void* data )
{
	free( data );
	data = NULL;
}

void hm_free( HashMap* map ) { hm_free_( map, default_node_dealloc_fn ); }

static size_t hash_idx( size_t hash, size_t map_size )
{
	// return hash % map_size;
	return hash & ( map_size - 1 );
}

/*
 * Pre-conditions: assumes the "map" argument is a non-null pointer to
 *                 a valid non-null HashMap*
 */
static void hm_insert_( HashMap** const map, void const* key, void const* value,
						bool rebalancing )
{
	if( !rebalancing && ( *map )->elements >= 0.8 * ( *map )->size ) {
		hm_rebalance_( map, ( *map )->size * 4 );
	}

	size_t hsh = ( *map )->hash_fn( key );
	size_t idx = hash_idx( hsh, ( *map )->size );

	LinkedList* llist = ( *map )->buckets[idx];

	if( llist->head != NULL ) {
		hm_debug_collisions_incr( map );
	}

	// TODO: error handling
	HashNode_* node = malloc( sizeof( HashNode_ ) );
	// TODO: memcpy?
	node->key = key;
	node->value = value;
	ll_push_front_alloc( &llist, node, sizeof( HashNode_ ) );

	( *map )->elements++;
}

static void hm_rebalance_( HashMap** const map, size_t new_size )
{
	HashMap* tmp;
	hm_create_( &tmp, NULL, NULL, new_size );

	if( tmp != NULL ) {
		tmp->hash_fn = ( *map )->hash_fn;
		tmp->cmp_fn = ( *map )->cmp_fn;
		tmp->dealloc_fn = ( *map )->dealloc_fn;
		size_t i = 0;
		for( ; i < ( *map )->size; ++i ) {
			LinkedList* llist = ( *map )->buckets[i];
			LinkedListNode_* node = llist->head;
			while( node != NULL ) {
				hm_insert_( &tmp, ( (HashNode_*)node->data )->key,
							( (HashNode_*)node->data )->value, true );
				node = node->next;
			}
		}

		hm_free( *map );
		*map = tmp;
	}
}

void hm_insert( HashMap** const map, void const* key, void const* value )
{
	hm_insert_( map, key, value, false );
}

void const* hm_get( HashMap const* map, void const* key )
{
	size_t hsh = map->hash_fn( key );
	size_t idx = hash_idx( hsh, map->size );

	LinkedList const* llist = map->buckets[idx];

	HashNode_* node_data;
	LL_FOR_EACH_BEGIN( node_data, llist )
	if( map->cmp_fn( node_data->key, key ) ) return node_data->value;
	LL_FOR_EACH_END()

	return NULL;
}

void hm_set_dealloc_fn( HashMap** map, void ( *fn )( void* ) )
{
	( *map )->dealloc_fn = fn;
}

static size_t default_hash_str_( void const* key )
{
	return hash_str_djb( (char const*)key );
}

static bool default_cmp_str_( void const* e1, void const* e2 )
{
	return strcmp( (char*)e1, (char*)e2 ) == 0;
}

static size_t default_hash_int_( void const* key )
{
	// TODO: deal with negative hashes; _Generic
	int32_t n = *(int32_t*)key;
	return hash_int_32( abs( n ) );
}

static size_t default_hash_ptr_( void const* key )
{
	// TODO: change uint64_t*; _Generic
	return hash_int_64( (uintptr_t)key );
}

static bool default_cmp_int_( void const* e1, void const* e2 )
{
	return *(int*)e1 == *(int*)e2;
}

static bool default_cmp_ptr_( void const* e1, void const* e2 )
{
	return (uintptr_t)e1 == (uintptr_t)e2;
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
	HM_FOR_EACH_BUCKET_BEGIN( llist, map )
	if( llist->size != 0 ) {
		printf( "Bucket %ld\n", i );
		if( print_fn != NULL )
			ll_print_custom( llist, print_fn );
		else
			ll_print( llist );
	}
	HM_FOR_EACH_BUCKET_END()
}

HashPair* hm_find( HashMap const* map, void const* key )
{
	HM_FOR_EACH_BEGIN( elem, map )
	if( map->cmp_fn( elem->key, key ) ) return elem;
	HM_FOR_EACH_END()

	return NULL;
}

void hm_remove( __attribute((unused))HashMap const* map, __attribute((unused))void const* key )
{
	// FIXME
}
