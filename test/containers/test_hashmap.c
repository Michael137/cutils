#include <assert.h> // assert
#include <stdio.h>
#include <string.h>

#include <containers/hashmap.h>

int main()
{
	printf( "~~~ Starting Hashmap Tests ~~~\n" );

	HashMap* map;

	hm_create( &map );
	hm_insert( &map, "Key1", "Value1" );
	char const* val = hm_get( map, "Key1" );
	assert( strcmp( "Value1", val ) == 0 );

	hm_free( &map );

	return 0;
}
