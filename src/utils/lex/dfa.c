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

typedef struct State_ {
	char const* state_id;
	bool is_accepting;
} State;

typedef struct DFA_ {
	State start_state;
	HashMap* dtrans;
} DFA;

int main() {
	DFA* dfa = malloc( sizeof(DFA) );
	State s0;
	s0.state_id = "A";
	s0.is_accepting = true;
	hm_create_str2str( &(dfa->dtrans) );
	dfa->start_state = s0;
	hm_insert(&(dfa->dtrans), s0.state_id, "a");

	hm_free( dfa->dtrans );
	free( dfa );
	return 0;
}
