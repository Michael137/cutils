#ifndef NARY_TREE_H
#define NARY_TREE_H

#include <stddef.h>
#include <utils/debug.h>

#define NT_SET_DBGSTR( container, msg ) SET_DBGSTR( NT_DEBUG, container, msg )

typedef struct TreeNode_
{
	// 36b
	struct TreeNode_* next;  // sibling node to the right
	struct TreeNode_* prev;  // sibling node to the left
	struct TreeNode_* child; // first child node
	struct TreeNode_* parent;

	// 8b
	void* data;

#if NT_DEBUG
	// 8b
	char* dbgStr;
#endif

} NTreeNode;

typedef struct Tree_
{
	// 52b
	struct TreeNode_* root;

	// 8b
	size_t size;

#if NT_DEBUG
	// 8b
	char* dbgStr;
#endif
} NTree;

void nt_create( NTree** tree );
void nt_free( NTree* tree );

void nt_insert( NTree** tree, void const* data );

#endif // NARY_TREE_H
