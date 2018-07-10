#ifndef AUTOMATA_IN_H
#define AUTOMATA_IN_H

#include <containers/hashmap.h>
#include <containers/linked_list.h>

// Example DFA using transition table:

// DFA State|c1|c2|
// ----------------
//     A    |B |C |
//     B    |B |C |
//     C    |B |C |
// ----------------

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

typedef struct FiniteAutomaton {
	State start_state;

	// Map<Trans, State>
	HashMap* transT;
	LinkedList* trans_buf_;
} FA, DFA, NFA;

typedef struct Transition_ {
	State start;
	State end;
	char const* symbol;
} Trans, Transition;

void fa_create( FA** fa );
void fa_free( FA* fa );
void fa_insert( FA* const* const fa, State const* s1, char const* sym,
				State const* s2 );
State const* fa_get( FA* fa, Trans const* trans );

void dfa_create( DFA** dfa );
void dfa_free( DFA* const dfa );
State const* dfa_get( DFA* dfa, Trans const* trans );
void dfa_insert( DFA* const* const dfa, State const* s1, char const* sym,
				 State const* s2 );
void dfa_trans_print( DFA const* const dfa );

#endif // AUTOMATA_IN_H
