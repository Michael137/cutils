#ifndef FIND_CYCLE_H_IN
#define FIND_CYCLE_H_IN

#include <stdbool.h>
#include <containers/linked_list.h>

// Adjacency list
// E.g.: [[0, 1], [1, 2], [0, 3], [3, 1]]
//
// Implementation possibilities:
// * Array of neighbouring vertex lists
// * Dictionary from vertex to list of neighbouring vertex
typedef struct adj_list_ {
	LinkedList** vertices;
} adj_list;

// Using dfs by coloring vertices and detecting back-edges
bool dfs_color_has_cycle();

#endif // FIND_CYCLE_H_IN
