#ifndef TRIE_H_IN
#define TRIE_H_IN

#include <containers/trie_internals.h>

typedef struct Trie_
{
	TrieNode* root;
} Trie;

void t_create( Trie** trie );
void t_insert( Trie** trie, char const* str );
bool t_search( Trie* trie, char const* str );
void t_free( Trie* trie );

#endif // TRIE_H_IN
