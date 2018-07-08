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
// or
// * Map<State,Map<Symbol,State>>: m1 = map("A"); m1("c1");
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

	// Map<Trans, State>
	HashMap* transT;
} FA, DFA, NFA;

typedef struct Transition_ {
	State start;
	State end;
	char const* symbol;
} Trans;

void fa_create( FA** fa )
{
	*fa = malloc( sizeof(FA) );
	hm_create( &((*fa)->transT), NULL, NULL );
}

void dfa_create( DFA** dfa )
{
	fa_create( dfa );
}

void fa_free( FA* fa )
{
	hm_free( fa->transT );
	fa->transT = NULL;

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
