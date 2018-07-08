#include <assert.h> // assert
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>

static void test_str2str()
{
	HashMap* str_map;
	hm_create_str2str( &str_map );
	char* allocated = strdup("Allocated");
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
	assert( strcmp( "Value3", val ) == 0 );
	printf( "%s\n", val );
	hm_free( int2str_map );
}

// Test defines
#define MAP_SZ 10000
#define BUF_SZ 20
#define BUF_MSG "Val%016d"
#define BUF_SPRINTF( buffer ) snprintf( buffer, BUF_SZ, BUF_MSG, i );
static void test_resize()
{
	HashMap* map;
	hm_create_str2str( &map );
	size_t old_size = map->size;

	char buffs[MAP_SZ][BUF_SZ];
	for( int i = 0; i < MAP_SZ; ++i ) {
		BUF_SPRINTF( buffs[i] );
		hm_insert( &map, buffs[i], buffs[i] );
	}

	for( int i = 0; i < MAP_SZ; ++i ) {
		assert( buffs[i] == (char const*)hm_get( map, buffs[i] ) );
	}

	assert( map->size != old_size );
	HM_DEBUG_LOG( map );
	hm_free( map );
}

int main()
{
	printf( "~~~ Starting Hashmap Tests ~~~\n" );

	test_str2str();
	test_str2int();
	test_int2str();
	test_int2int();

	test_resize();

	return 0;
}
