#include <containers/nary_tree.h>
#include <stdlib.h>

void nt_create( NTree** tree )
{
	// TODO: handle errors
	*tree = malloc( sizeof( NTree ) );

	( *tree )->root = NULL;
	( *tree )->size = 0;

	NT_SET_DBGSTR( ( *tree ), "NTree Created" );
}

void nt_free( NTree* tree )
{
	free( tree );
	tree = NULL;
}
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
void nt_insert( NTree** tree, void const* data ) {}
#pragma GCC diagnostic pop
