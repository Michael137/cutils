#ifndef TRIE_INTERNALS_H_IN
#define TRIE_INTERNALS_H_IN

#include <stdbool.h>
#include <ctype.h>

#define ALPHABET_SZ 26
#define ASSERT_WORD( container, str )                                          \
	if( t_search( container, str ) ) printf( "Found %s!\n", str );

typedef struct TrieNode_
{

	struct TrieNode_* children[ALPHABET_SZ];
	bool is_word_end;

} TrieNode;

// ASCII: 97-122 (a-z)
// E.g.: 'a' -> 97 - 97 == 0
static inline int t_idx_from_char( char letter ) { return tolower( letter ) - 'a'; }

void t_create_node( TrieNode** node );
void t_insert_node( TrieNode** node, char const* str );
bool t_search_from_node( TrieNode* node, char const* str );
void t_free_node( TrieNode* node );

#endif // TRIE_INTERNALS_H_IN
