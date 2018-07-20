#ifndef NARY_TREE_H
#define NARY_TREE_H

typedef struct TreeNode_ {
	// 36b
	NTreeNode_* next;	// sibling node to the right
	NTreeNode_* prev;	// sibling node to the left
	NTreeNode_* child;	// first child node
	NTreeNode_* parent;

	// 8b
	void* data;

#if NT_DEBUG
	// 8b
	char* dbgStr;
#endif

} NTreeNode;

typedef struct Tree_ {
	// 52b
	TreeNode_* root;

	// 8b
	size_t size;

#if NT_DEBUG
	// 8b
	char* dbgStr;
#endif
} NTree;

void nt_create( NTree* tree );
void nt_free( NTree* tree );

void nt_insert( NTree** tree, void const* data );

#endif // NARY_TREE_H
