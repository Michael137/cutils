#include <assert.h>
#include <string.h>

#include <utils/automata.h>

int main()
{
	DFA* dfa;
	dfa_create( &dfa );

	State s0 = {"A", false};
	State s1 = {"B", true};
	dfa_insert( &dfa, &s0, "b", &s1 );

	Trans* trans;
	LL_FOR_EACH_BEGIN( trans, dfa->trans_buf_ )
	assert( strcmp( s1.state_id,
					( (State*)dfa_get( dfa, trans ) )->state_id ) == 0 );
	LL_FOR_EACH_END()

	dfa_trans_print( dfa );

	dfa_free( dfa );
	return 0;
}
