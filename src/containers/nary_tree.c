#include <containers/nary_tree.h>
#include <stdlib.h>
// TODO

static void insert_sibling( NTreeNode** node, void* const data )
{
	NTreeNode* tmp = *node;
	while( tmp->next != NULL )
		tmp = tmp->next;

	NTreeNode* new_node = malloc( sizeof( NTreeNode ) );

	tmp->next = new_node;
	tmp->data = data;
	new_node->next = NULL;
}

static void __attribute( ( unused ) ) insert_child() {}

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

void nt_insert( NTree** tree, void* const data )
{
	if( ( *tree )->root != NULL ) insert_sibling( &( ( *tree )->root ), data );
}
