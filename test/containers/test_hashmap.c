#include <assert.h> // assert
#include <containers/hashmap.h>
#include <stdio.h>

int main()
{
	printf( "~~~ Starting Hashmap Tests ~~~\n" );

	HashMap* map;

	hm_create( &map );
	hm_insert( &map, "Key1", "Value1" );
	char const* val = hm_get( map, "Key1" );
	printf( "%s\n", val );

	hm_free( map );

	return 0;
}
