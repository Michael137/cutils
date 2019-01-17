#include <stdio.h>
#include <stdlib.h>

#include <containers/hashmap.h>
#include <containers/linked_list.h>

#include <utils/graph/find_cycle.h>

#include <stdbool.h>

void adjl_create( adj_list** lst, size_t num_vertices )
{
	( *lst )               = malloc( sizeof( adj_list ) );
	( *lst )->vertices     = calloc( num_vertices, sizeof( LinkedList ) );
	( *lst )->num_vertices = num_vertices;

	for( size_t i = 0; i < num_vertices; ++i )
	{
		ll_create( &( ( *lst )->vertices[i] ) );
	}
}

void adjl_free( adj_list* lst )
{
	for( size_t i = 0; i < lst->num_vertices; ++i )
		ll_free( lst->vertices[i] );
	free( lst->vertices );
	free( lst );
}

bool dfs_color_has_cycle()
{
	puts( "TO BE IMPLEMENTED" );
	return false;
}
