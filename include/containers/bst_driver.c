#include <bst.h>

int main() {
	bst_tree* tree = malloc(sizeof(bst_tree));
	bst_insert(&tree, 3, INT);
	bst_insert(&tree, 1, INT);
	bst_insert(&tree, 15, INT);
	bst_insert(&tree, 4, INT);
	bst_insert(&tree, 0, INT);
	bst_print(tree->root, PREORDER);
	return 0;
}
