#include <containers/nary_tree.h>
#include <stdio.h>

int main() {
	puts("TEST STUB FOR NT");

	NTree* tree;
	nt_create( &tree );
	nt_insert( &tree, "Root Node" );
	nt_insert( &tree, "Node 1" );
	nt_insert( &tree, "Node 2" );
	nt_free( tree );
	return 0;
}
