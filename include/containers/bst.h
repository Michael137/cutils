#ifndef BST_H_IN
#define BST_H_IN

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

enum NodeType {
	VOID_PTR,
	INT,
	CHAR_PTR
};

typedef struct bst_node_ {
	struct bst_node_* left;
	struct bst_node_* right;
	struct bst_node_* parent;

#if BST_DEBUG
	char* dbgStr;
#endif

//	void* data;
	int data;
} bst_node;

typedef struct bst_tree_ {
	bst_node* root;

#if BST_DEBUG
	char* dbgStr;
#endif
} bst_tree;

// make node
// insert node
// delete
// search
// contains
// minimum
// maximum
// predecessor
// successor

enum BstTraversalOrders {
	PREORDER,
	INORDER,
	POSTORDER
};


void bst_print(bst_node* node, int order ) {
	if(node == NULL)
		return;
	else {
		printf("node->data: %d\n", node->data);
		bst_print(node->left, order);
		bst_print(node->right, order);
	}
}

int bst_insert(bst_tree** tree, int value, int node_type) {
	bst_node* new_parent = NULL;
	bst_node* it = (*tree)->root;

	bst_node* node = malloc(sizeof(bst_node));
	node->data = value;

	while(it != NULL) {
		new_parent = it;
		if(node->data < it->data)
			it = it->left;
		else
			it = it->right;
	}

	node->parent = new_parent;
	if(new_parent == NULL) { // Passed in tree was empty
		(*tree)->root = node;
	} else if(node->data < new_parent->data) // Maintain BST property
		new_parent->left = node;
	else {
		new_parent->right = node;
	}
}

// int bst_create(bst_tree** tree);

#endif // BST_H_IN
