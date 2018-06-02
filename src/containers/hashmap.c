#include <stdio.h>
#include <stdlib.h>

#include <containers/hashmap.h>

static size_t const sc_hm_min_size_ = 50;

int hm_create( HashMap** map )
{
	*map = malloc( sizeof( HashMap ) + sc_hm_min_size_ * sizeof( LinkedList ) );
	if( map && *map )
	{
		(*map)->size = sc_hm_min_size_;
		return HM_SUCCESS;
	}
	else
	{
		return HM_INVALID_ARGS;
	}

	return HM_FAILURE;
}

void hm_free( HashMap* map )
{
	free( map );
	map = NULL;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void hm_insert( HashMap** map, void const* key, void const* value ) {}
void* hm_get( HashMap const* map, void const* key ) { return (char*) key; }
#pragma GCC diagnostic pop
