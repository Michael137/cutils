#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SZ 26

typedef struct TrieNode_
{

	struct TrieNode_* children[ALPHABET_SZ];
	bool is_word_end;

} TrieNode;

// ASCII: 97-122
int t_idx_from_char( char letter )
{
	int hash = letter - '0';
	return hash - 97;
}

void t_create_node( TrieNode** node )
{
	( *node ) = malloc( sizeof( TrieNode ) );
	for( int i = 0; i < ALPHABET_SZ; ++i )
		( *node )->children[i] = NULL;

	( *node )->is_word_end = false;
}

void t_insert( TrieNode** node, char const* str )
{
	TrieNode* trav = *node;
	for( int i = 0; str[i] != '\0'; ++i ) {
		int idx = t_idx_from_char( tolower( str[i] ) );

		if( trav->children[idx] == NULL )
			t_create_node( &( trav->children[idx] ) );

		trav = trav->children[idx];
	}

	trav->is_word_end = true;
}

bool t_search( TrieNode* node, char const* str )
{
	TrieNode* tmp = node;
	for( int i = 0; str[i] != '\0'; ++i ) {
		int idx = t_idx_from_char( tolower( str[i] ) );

		if( tmp->children[idx] == NULL ) return false;

		tmp = tmp->children[idx];
	}

	return tmp->is_word_end;
}

void t_free() {}

int main()
{
	TrieNode* root;
	t_create_node( &root );
	t_insert( &root, "Hell" );
	t_insert( &root, "Hellorun" );
	//	t_insert( &root, "Hello" );
	//	t_insert( &root, "Hellboy" );
	//	t_insert( &root, "World" );

	if( t_search( root, "Hell" ) ) printf( "Found Hell!\n" );
	if( t_search( root, "Hello" ) ) printf( "Found Hello!\n" );
	if( t_search( root, "Hellorun" ) ) printf( "Found Hellorun!\n" );
	if( t_search( root, "Hel" ) ) printf( "Found Hel!\n" );

	return 0;
}
