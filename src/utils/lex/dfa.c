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
	HashMap* const dtrans;
} DFA;

int main() { return 0; }
