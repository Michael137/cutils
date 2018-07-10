#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <containers/hashmap.h>
#include <containers/linked_list.h>
#include <core/hash.h>
#include <utils/automata.h>

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
	char const* s0 = ( key->start ).state_id;
	char const* sym = key->symbol;
	puts( ">> \tdata:\n>> " );
	printf( ">> \t%4s\n", sym );
	printf( ">> \t%s", s0 );
	if( ( key->start ).is_accepting ) printf( " (final)" );
	printf( " ----> %s", s1.state_id );
	if( s1.is_accepting ) printf( " (final)" );

	puts( "\n>> " );
}

/*
 * FA APIs
 */
void fa_create( FA** fa )
{
	*fa = malloc( sizeof( FA ) );
	hm_create( &( ( *fa )->transT ), trans_hash_fn, trans_cmp_fn );
	ll_create( &( ( *fa )->trans_buf_ ) );
}

void fa_free( FA* fa )
{
	hm_free( fa->transT );
	fa->transT = NULL;

	ll_free( fa->trans_buf_ );
	fa->trans_buf_ = NULL;

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
	ll_push_front_alloc( &( ( *fa )->trans_buf_ ), trans,
						 sizeof( Transition ) );
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
