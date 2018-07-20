#include <containers/nary_tree.h>
#include <stdio.h>

int main() {
	puts("TEST STUB FOR NT");

	NTree* tree;
	nt_create( &tree );
	nt_free( tree );
	return 0;
}
