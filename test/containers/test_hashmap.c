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

int main()
{
	printf( "~~~ Starting Hashmap Tests ~~~\n" );

	HashMap* map;

	hm_create( &map, hash_fn_str, cmp_fn_str );
	hm_insert( &map, "Key1", "Value1" );
	hm_insert( &map, "Key2", "Value2" );
	hm_insert( &map, "Key3", "Value3" );
	char const* val = hm_get( map, "Key1" );
	assert( strcmp( "Value1", val ) == 0 );
	printf( "%s\n", val );

	hm_free( map );

	return 0;
}
