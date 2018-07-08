#include <stdio.h>
#include <stdlib.h>

#include <containers/hashmap.h>

// Example DFA using transition table:

// DFA State|c1|c2|
// ----------------
//     A    |B |C |
//     B    |B |C |
//     C    |B |C |
// ----------------

// DFA Structure:
// * Map<Pair<State,Symbol>,State>
// ** Map<State,Map<Symbol,State>>: m1 = map("A"); m1("c1");
// * Start state

// State
// * ID
// * Accepting State?

// API
// * create
// * delete
// * next
// * show
// * add(Start State, Symbol, End State)
// (* last)

// Example usage for DFA:
// FA* fa = malloc(sizeof(FA));
// dfa_create(&fa)
// fa_insert({"s_n", "b", "s_0"})
// fa_change({"s_n", "b", "s_0", "s_1"})

typedef struct State_ {
	char const* state_id;
	bool is_accepting;
} State;

typedef struct FiniteAutomaton {
	State start_state;
	HashMap* trans;
} FA, DFA, NFA;

void fa_create( FA** fa )
{
	*fa = malloc( sizeof(FA) );
	hm_create( &((*fa)->trans), NULL, NULL );
//	State s0;
//	s0.state_id = "A";
//	s0.is_accepting = true;
//	(*fa)->start_state = s0;
//	hm_insert(&((*fa)->trans), s0.state_id, "a");
}

void dfa_create( DFA** dfa )
{
	fa_create( dfa );
}

void fa_free( FA* fa )
{
	hm_free( fa->trans );
	fa->trans = NULL;

	free( fa );
	fa = NULL;
}

void dfa_free( DFA* const dfa )
{
	fa_free( dfa );
}

int main() {
	DFA* dfa;
	dfa_create( &dfa );
	dfa_free( dfa );
	return 0;
}
