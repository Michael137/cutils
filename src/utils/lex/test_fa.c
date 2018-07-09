#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>
#include <containers/linked_list.h>
#include <core/hash.h>

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
// FA* fa
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

// TODO: consolidate hash fns throughout all projs
static size_t trans_hash_fn( void const* key )
{
	Trans const* tmp = key;
	char str[strlen( ( tmp->start ).state_id ) +
			 strlen( ( tmp->end ).state_id ) + strlen( tmp->symbol ) + 1];
	snprintf( str, sizeof( str ), "%s%s%s", ( tmp->start ).state_id,
			  ( tmp->end ).state_id, tmp->symbol );

	return hash_str_djb( str );
}

static bool trans_cmp_fn( void const* key, void const* value )
{
	Trans const* tmp_k = key;
	Trans const* tmp_v = value;

	return ( strcmp( ( tmp_k->start ).state_id, ( tmp_v->start ).state_id ) ) ==
			   0 &&
		   ( strcmp( ( tmp_k->start ).state_id, ( tmp_v->start ).state_id ) ) ==
			   0 &&
		   ( strcmp( tmp_k->symbol, tmp_v->symbol ) == 0 );
}

static void trans_print_fn( LinkedListNode_ const* node )
{
	HashNode_ const* h_node = node->data;
	Trans const* key = h_node->key;
	State s1 = *(State*)h_node->value;
	puts( "\ttype: Transition" );
	char const* s0 = (key->start).state_id;
	char const* sym = key->symbol;
	puts( ">> \tdata:\n>> " );
	printf( ">> \t%4s\n", sym );
	printf( ">> \t%s", s0 );
	if( (key->start).is_accepting )
		printf( " (final)" );
	printf(" ----> %s", s1.state_id);
	if( s1.is_accepting )
		printf( " (final)" );

	puts( "\n>> " );
}

void fa_create( FA** fa )
{
	*fa = malloc( sizeof( FA ) );
	hm_create( &( ( *fa )->transT ), trans_hash_fn, trans_cmp_fn );
}

void dfa_create( DFA** dfa ) { fa_create( dfa ); }

void fa_free( FA* fa )
{
	hm_free( fa->transT );
	fa->transT = NULL;

	free( fa );
	fa = NULL;
}

void dfa_free( DFA* const dfa ) { fa_free( dfa ); }

Trans* fa_insert( FA* const* const fa, State const* s1, char const* sym, State const* s2 )
{
	Trans* trans = malloc( sizeof( Trans ) );
	trans->start = *s1;
	trans->end = *s2;
	trans->symbol = sym;
	hm_insert( &( ( *fa )->transT ), trans, s2 );
	return trans;
}

int main()
{
	DFA* dfa;
	dfa_create( &dfa );

	State s0 = {"A", false};
	State s1 = {"B", true};
	Trans* trans = fa_insert( &dfa, &s0, "b", &s1 );
	State found = *(State*)hm_get( dfa->transT, trans );
	printf( "%s %ld\n", found.state_id, strlen(found.state_id) );

	hm_print( dfa->transT, trans_print_fn );

	dfa_free( dfa );
	free( trans );
	return 0;
}