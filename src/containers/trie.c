#include <containers/trie.h>
#include <containers/trie_internals.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void t_create( Trie** trie )
{
	( *trie ) = malloc( sizeof( Trie ) );
	t_create_node( &( ( *trie )->root ) );
}

void t_insert( Trie** trie, char const* str )
{
	t_insert_node( &( ( *trie )->root ), str );
}

bool t_search( Trie* trie, char const* str )
{
	return t_search_from_node( trie->root, str );
}

void t_free( Trie* trie )
{
	t_free_node( trie->root );
	free( trie );
	trie = NULL;
}
