#include <assert.h> // assert
#include <stdio.h>
#include <string.h>

#include <containers/hashmap.h>

static size_t hash_fn_str( void const* key )
{
	size_t hash = 5381;
	char const* str = (char const*)key;
	int c;

	while ((c = *str++))
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

static bool cmp_fn_str( void const* key, void const* value )
{
	return strcmp( (char*)key, (char*)value ) == 0;
}

static size_t hash_fn_int( void const* num )
{
	size_t key = *(int*)num;
	key = (~key) + (key << 21); // key = (key << 21) - key - 1;
	key = key ^ (key >> 24);
	key = (key + (key << 3)) + (key << 8); // key * 265
	key = key ^ (key >> 14);
	key = (key + (key << 2)) + (key << 4); // key * 21
	key = key ^ (key >> 28);
	key = key + (key << 31);
	return key;
}

static bool cmp_fn_int( void const* key, void const* value )
{
	return *(int*)key == *(int*)value;
}

int main()
{
	printf( "~~~ Starting Hashmap Tests ~~~\n" );

	HashMap* str_map;

	hm_create( &str_map, hash_fn_str, cmp_fn_str );
	hm_insert( &str_map, "Key1", "Value1" );
	hm_insert( &str_map, "Key2", "Value2" );
	hm_insert( &str_map, "Key3", "Value3" );
	char const* val = hm_get( str_map, "Key1" );
	assert( strcmp( "Value1", val ) == 0 );
	printf( "%s\n", val );

	hm_free( str_map );

	HashMap* int_map;

	hm_create( &int_map, hash_fn_int, cmp_fn_int );
	int val1 = 1;
	int val2 = 2;
	int val3 = 3;
	hm_insert( &int_map, "Key1", &val1 );
	hm_insert( &int_map, "Key2", &val2 );
	hm_insert( &int_map, "Key3", &val3 );
	int num = *(int*)hm_get( int_map, "Key1" );
	assert( strcmp( "Value1", val ) == 0 );
	printf( "%d\n", num );

	hm_free( int_map );

	return 0;
}
