#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>
#include <containers/linked_list_internal.h>

#include <utils/graph/find_cycle.h>

int main()
{
	puts( "~~~ Starting test_find_cycle ~~~" );
	int vs[] = { 1, 2, 3, 4, 5 };
	adj_list* lst = NULL;
	adjl_create( &lst, sizeof(vs)/sizeof(vs[0]));

	// insert( &lst, [1, 2] );
	adjl_free( lst );

	return 0;
}
