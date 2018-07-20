#ifndef HASHMAP_H_IN
#define HASHMAP_H_IN

#include <containers/linked_list.h>
#include <utils/debug.h> // debug_more_

// TODO: consolidate error handling mechanisms
// HashMap Constats
#define HM_FAILURE -1
#define HM_SUCCESS 1
#define HM_INVALID_ARGS 2

typedef struct HashNode_
{

	void const* key;
	void const* value;

} HashNode_, HashPair;

typedef struct HashMap_
{

	size_t size;
	size_t elements;

#if HM_DEBUG
	size_t collisions_;
	char* dbgStr;
#endif

	size_t ( *hash_fn )( void const* );
	bool ( *cmp_fn )( void const*, void const* );
	void ( *dealloc_fn )( void* );

	// Array of hash buckets of hash nodes
	LinkedList** buckets;

} HashMap;

int hm_create( HashMap** map, size_t ( *hash_fn )( void const* ),
			   bool ( *cmp_fn )( void const*, void const* ) );
int hm_create_str( HashMap** map );
int hm_create_int( HashMap** map );
int hm_create_ptr( HashMap** map );

void hm_free( HashMap* map );
void hm_free_custom( HashMap* map, void ( *dealloc_fn )( void* ) );

// TODO: hm_insert with option to call set_node_type()
void hm_insert( HashMap** const map, void const* key, void const* value );
void hm_insert_typed( HashMap** const map, void const* key, void const* value );
void const* hm_get( HashMap const* map, void const* key );

void hm_print( HashMap const* const,
			   void ( *print_fn )( LinkedListNode_ const* ) );

size_t hm_debug_get_collisions( HashMap const* map );
void hm_set_dealloc_fn( HashMap**, void ( *fn )( void* ) );
HashPair* hm_find( HashMap const*, void const* key );
void hm_remove( HashMap**, void const* key );

// TODO: add bucket distribution info and average load factor
#define HM_DEBUG_LOG( map )                                                    \
	do {                                                                       \
		DEBUG_MORE_( HM_DEBUG, "%s (%ldE:%ldB:%ldC)\n",                        \
					 DBGSTR( HM_DEBUG, map ), ( map )->elements,               \
					 ( map )->size,                                            \
					 DBG_CONTAINER_MEM( HM_DEBUG, map, collisions_, 0UL ) );   \
	} while( 0 )

#define HM_FOR_EACH_BUCKET_BEGIN( var, map )                                   \
	LinkedList const* var = NULL;                                              \
	size_t _hm_ctr = 0;                                                        \
	for( ; _hm_ctr < ( map )->size; ++_hm_ctr ) {                              \
		var = ( map )->buckets[_hm_ctr];

#define HM_FOR_EACH_BUCKET_END() }

#define HM_FOR_EACH_BEGIN( var, map )                                          \
	HashNode_* var;                                                            \
	HM_FOR_EACH_BUCKET_BEGIN( _hm_buckets, ( map ) )                           \
	LL_FOR_EACH_BEGIN( var, _hm_buckets )

#define HM_FOR_EACH_END()                                                      \
	LL_FOR_EACH_END()                                                          \
	HM_FOR_EACH_BUCKET_END()

#define HM_SET_DBGSTR( container, msg ) SET_DBGSTR( HM_DEBUG, container, msg )
#define HM_SET_DBG_CONTAINER_MEM( container, member, value )                   \
	SET_DBG_CONTAINER_MEM( HM_DEBUG, container, member, value )

#endif // HASHMAP_H_IN
