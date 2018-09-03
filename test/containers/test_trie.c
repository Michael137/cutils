#include <containers/trie.h>
#include <stdio.h>

int main()
{
	Trie* trie;
	t_create( &trie );

	t_insert( &trie, "Hello" );
	t_insert( &trie, "Hellorun" );

	ASSERT_WORD( trie, "Hell" );
	ASSERT_WORD( trie, "Hello" );
	ASSERT_WORD( trie, "HELLO" );
	ASSERT_WORD( trie, "Hello" );
	ASSERT_WORD( trie, "Hellorun" );
	ASSERT_WORD( trie, "Hel" );

	t_free( trie );

	return 0;
}
