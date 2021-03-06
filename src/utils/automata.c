#include <containers/hashmap.h>
#include <containers/linked_list.h>
#include <core/hash.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utils/automata.h>

static size_t trans_hash_fn( void const* key )
{
	Trans const* tmp = key;
	char str[strlen( ( tmp->start ).state_id ) +
			 strlen( ( tmp->end ).state_id ) + strlen( tmp->symbol ) + 1];
	snprintf( str, sizeof( str ), "%s%s%s", ( tmp->start ).state_id,
			  ( tmp->end ).state_id, tmp->symbol );

	return hash_str_djb2( str );
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
	char const* s0 = ( key->start ).state_id;
	char const* sym = key->symbol;
	puts( ">> \tdata:\n>> " );
	printf( ">> \t%4s\n", sym );
	printf( ">> \t%s", s0 );
	printf( " ----> %s", s1.state_id );
	if( s1.is_accepting ) printf( " (final)\n>> " );
	if( ( key->start ).is_accepting ) printf( " (final)" );
	puts( "\n>> " );
}

// TODO: general key dealloc fn in parameterized macro
void trans_node_dealloc_fn( void* node )
{
	void const* key = ( (HashNode_*)node )->key;
	Transition* trans = (Transition*)key;

	free( trans );
	trans = NULL;

	free( node );
	node = NULL;
}
/*
 * FA APIs
 */
void fa_create( FA** fa )
{
	*fa = malloc( sizeof( FA ) );
	hm_create( &( ( *fa )->transT ), trans_hash_fn, trans_cmp_fn );
}

void fa_free( FA* fa )
{
	hm_free_custom( fa->transT, trans_node_dealloc_fn );
	fa->transT = NULL;

	free( fa );
	fa = NULL;
}

void fa_insert( FA* const* const fa, State const* s1, char const* sym,
				State const* s2 )
{
	Trans* trans = malloc( sizeof( Trans ) );
	trans->start = *s1;
	trans->end = *s2;
	trans->symbol = sym;
	hm_insert( &( ( *fa )->transT ), trans, s2 );
}

State const* fa_get( FA* fa, Trans const* trans )
{
	return (State const*)hm_get( fa->transT, trans );
}

/*
 * DFA APIs
 */
void dfa_create( DFA** dfa ) { fa_create( dfa ); }

void dfa_free( DFA* const dfa ) { fa_free( dfa ); }

State const* dfa_get( DFA* dfa, Trans const* trans )
{
	return fa_get( dfa, trans );
}

void dfa_insert( DFA* const* const dfa, State const* s1, char const* sym,
				 State const* s2 )
{
	fa_insert( dfa, s1, sym, s2 );
}

void dfa_trans_print( DFA const* const dfa )
{
	hm_print( dfa->transT, trans_print_fn );
}
