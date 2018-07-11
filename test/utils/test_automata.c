#include <assert.h>
#include <string.h>

#include <utils/automata.h>

int main()
{
	DFA* dfa;
	dfa_create( &dfa );

	State s0 = {"A", false};
	State s1 = {"B", true};
	State s2 = {"C", true};
	dfa_insert( &dfa, &s0, "a", &s1 );
	dfa_insert( &dfa, &s0, "b", &s2 );
	dfa_insert( &dfa, &s1, "a", &s1 );
	dfa_insert( &dfa, &s1, "b", &s2 );
	dfa_insert( &dfa, &s2, "a", &s1 );
	dfa_insert( &dfa, &s2, "b", &s2 );
	dfa_trans_print( dfa );

	dfa_free( dfa );
	return 0;
}
