#include <assert.h> // assert
#include <containers/hashmap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// GNU Scientific Library
#include <gsl/gsl_rng.h> //

// Test defines
#define MAP_SZ 500000
#define BUF_SZ 20
#define BUF_MSG "Val%016d"
#define BUF_SPRINTF( buffer ) snprintf( buffer, BUF_SZ, BUF_MSG, i );

static void test_str2str()
{
	HashMap* str_map;
	hm_create_str2str( &str_map );
	char* allocated = strdup( "Allocated" );
	hm_insert( &str_map, "Key1", "Value1" );
	hm_insert( &str_map, "Key2", "Value2" );
	hm_insert( &str_map, "Key3", "Value3" );
	hm_insert( &str_map, "Key4", allocated );
	char const* val = hm_get( str_map, "Key1" );
	char const* val4 = hm_get( str_map, "Key4" );
	assert( strcmp( "Value1", val ) == 0 );
	assert( strcmp( allocated, val4 ) == 0 );
	printf( "%s\n", val );
	printf( "%s\n", val4 );
	hm_free( str_map );
	free( allocated );
}

static void test_str2int()
{
	HashMap* int_map;
	hm_create_str2int( &int_map );
	int val1 = -1231;
	int val2 = 31232;
	int val3 = 137;
	hm_insert( &int_map, "Key1", &val1 );
	hm_insert( &int_map, "Key2", &val2 );
	hm_insert( &int_map, "Key3", &val3 );
	int num = *(int*)hm_get( int_map, "Key1" );
	assert( num == val1 );
	printf( "%d\n", num );
	hm_free( int_map );
}

static void test_int2int()
{
	HashMap* int2int_map;
	hm_create_int2int( &int2int_map );
	int val1 = -1231;
	int val2 = 31232;
	int val3 = 137;
	int key1 = -121;
	int key2 = 21238;
	int key3 = 30198;
	hm_insert( &int2int_map, &key1, &val1 );
	hm_insert( &int2int_map, &key2, &val2 );
	hm_insert( &int2int_map, &key3, &val3 );
	int num = *(int*)hm_get( int2int_map, &key2 );
	assert( num == val2 );
	printf( "%d\n", num );
	hm_print( int2int_map, NULL );
	hm_free( int2int_map );
}

static void test_int2str()
{
	HashMap* int2str_map;
	hm_create_int2str( &int2str_map );
	int key1 = -121;
	int key2 = 21238;
	int key3 = 30198;
	hm_insert( &int2str_map, &key1, "Value1" );
	hm_insert( &int2str_map, &key2, "Value2" );
	hm_insert( &int2str_map, &key3, "Value3" );
	char const* val = hm_get( int2str_map, &key3 );
	char const* val_neg = hm_get( int2str_map, &key1 );
	assert( strcmp( "Value3", val ) == 0 );
	assert( strcmp( "Value1", val_neg ) == 0 );
	printf( "%s\n", val );
	hm_free( int2str_map );
}

static void test_resize()
{
	HashMap* map;
	hm_create_str2str( &map );
	size_t old_size = map->size;

	puts( "~~~> Starting HashMap insertion benchmark" );
	float start = (float)clock() / CLOCKS_PER_SEC;
	static char buffs[MAP_SZ][BUF_SZ];
	for( int i = 0; i < MAP_SZ; ++i ) {
		BUF_SPRINTF( buffs[i] );
		hm_insert( &map, buffs[i], buffs[i] );
	}
	float end = (float)clock() / CLOCKS_PER_SEC;
	printf( "\t~~~> %fs elapsed\n", end - start );

	puts( "~~~> Starting HashMap random fetch benchmark" );
	const gsl_rng_type* T;
	gsl_rng* r;
	gsl_rng_env_setup();
	T = gsl_rng_default;
	r = gsl_rng_alloc( T );
	size_t test_idx[MAP_SZ];
	for( int i = 0; i < MAP_SZ; ++i )
		test_idx[i] = gsl_rng_uniform_int( r, MAP_SZ );
	gsl_rng_free( r );
	start = (float)clock() / CLOCKS_PER_SEC;
	for( int i = 0; i < MAP_SZ; ++i ) {
		assert( buffs[test_idx[i]] ==
				(char const*)hm_get( map, buffs[test_idx[i]] ) );
	}
	end = (float)clock() / CLOCKS_PER_SEC;
	printf( "\t~~~> %fs elapsed\n", end - start );

	puts( "~~~> Starting HashMap sequential fetch benchmark" );
	for( int i = 0; i < MAP_SZ; ++i )
		test_idx[i] = i;
	start = (float)clock() / CLOCKS_PER_SEC;
	for( int i = 0; i < MAP_SZ; ++i ) {
		assert( buffs[test_idx[i]] ==
				(char const*)hm_get( map, buffs[test_idx[i]] ) );
	}
	end = (float)clock() / CLOCKS_PER_SEC;
	printf( "\t~~~> %fs elapsed\n", end - start );

	assert( map->size != old_size );
	HM_DEBUG_LOG( map );
	hm_free( map );
}

void test_print()
{
	HashMap* map;
	hm_create_str2str( &map );
	int old_size = map->size;

	char buffs[old_size * 2][BUF_SZ];
	for( int i = 0; i < old_size * 2; ++i ) {
		BUF_SPRINTF( buffs[i] );
		hm_insert( &map, buffs[i], buffs[i] );
	}
	hm_print( map, NULL );
	HM_DEBUG_LOG( map );
	hm_free( map );
}

void test_find()
{
	HashMap* map;
	hm_create_str2str( &map );
	hm_insert( &map, "Key 1", "Value 1" );
	hm_insert( &map, "Key 2", "Value 2" );
	hm_insert( &map, "Key 3", "Value 3" );
	HashPair* pair = hm_find( map, "Key 1" );
	assert( strcmp( (char const*)pair->key, "Key 1" ) == 0 );
	assert( strcmp( (char const*)pair->value, "Value 1" ) == 0 );
	pair = hm_find( map, "Invalid" );
	assert( pair == NULL );
	hm_free( map );
}

static void _test_remove_dealloc_fn( void* node )
{
	void const* key = ( (HashNode_*)node )->key;
	char* str = (char*)key;

	free( str );
	str = NULL;

	free( node );
	node = NULL;
}

void test_remove()
{
	HashMap* map;
	hm_create_str2int( &map );
	char* str1 = strdup( "Alloc 1" );
	char* str2 = strdup( "Alloc 2" );
	char* str3 = strdup( "Alloc 3" );
	int v1 = 100;
	int v2 = -100;
	int v3 = 0xDEADBEEF;
	hm_insert( &map, str1, &v1 );
	hm_insert( &map, str2, &v2 );
	hm_insert( &map, str3, &v3 );

	assert( *(int*)hm_get( map, str2 ) == v2 );
	hm_remove( &map, str2 );
	assert( hm_get( map, str2 ) == NULL );
	hm_free_custom( map, _test_remove_dealloc_fn );
	free( str2 );
}

int main()
{
	printf( "~~~ Starting Hashmap Tests ~~~\n" );

	test_print();
	test_int2str();
	test_int2int();
	test_str2str();
	test_str2int();
	test_find();
	test_remove();
	test_resize();

	return 0;
}
