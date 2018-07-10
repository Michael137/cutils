#include <assert.h> // assert
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <containers/linked_list.h>
#include <containers/linked_list_helpers.h>

// Test defines
#define LIST_SZ 20000
#define BUF_SZ 21
#define BUF_MSG "Node%016d"
#define BUF_SPRINTF( buffer, ctr ) snprintf( buffer, BUF_SZ, BUF_MSG, ctr );
void test_str_insert()
{
	LinkedList* llist;
	ll_create( &llist );

	for( int i = 0; i < LIST_SZ; ++i ) {
		char buf[BUF_SZ];
		BUF_SPRINTF( buf, i );
		ll_push_front( &llist, buf, BUF_SZ );
	}

	char buf[BUF_SZ];
	BUF_SPRINTF( buf, 25 );
	assert( strcmp( buf, (const char*)ll_at(
							 llist, ll_find_string( llist, buf ) ) ) == 0 );

	ll_free( llist );
}

void test_int_insert()
{
	LinkedList* llist;
	ll_create( &llist );

	for( int i = 0; i < LIST_SZ; ++i ) {
		ll_push_front( &llist, &i, sizeof( int ) );
	}

	int to_find = 493;
	assert( to_find == *(int*)ll_at( llist, ll_find_int( llist, &to_find ) ) );

	ll_free( llist );
}

void test_str_alloc()
{
	LinkedList* llist;
	ll_create( &llist );
	char* msg = strdup( "Allocated String Node" );
	ll_push_front( &llist, msg, strlen( msg ) + 1 );
	char* at_msg = ll_at( llist, 0 );
	assert( strcmp( at_msg, msg ) == 0 );
	free( msg );
	ll_free( llist );
}

void test_delete()
{
	LinkedList* llist;
	ll_create( &llist );

	for( int i = 0; i < LIST_SZ; ++i ) {
		ll_push_front( &llist, &i, sizeof( int ) );
	}

	size_t old_size = llist->size;
	for( int i = 0; i < LIST_SZ; ++i ) {
		if( i % 2 == 0 )
			ll_remove( &llist, 0 );
	}
	assert( llist->size == old_size / 2 );

	old_size = llist->size;
	for( size_t i = 0; i < old_size; ++i ) {
		ll_pop_front( &llist );
	}
	assert( llist->size == 0 );

	ll_free( llist );
}

void test_node_type()
{
	LinkedList* llist;
	ll_create( &llist );

	char const* cstr = "String";
	int int1 = 100;
	int int2 = -100;
	ll_push_front( &llist, cstr, strlen( cstr ) + 1 );
	ll_push_front( &llist, &int1, sizeof( int ) );
	ll_push_front( &llist, &int2, sizeof( int ) );
	ll_node_set_type( &llist, 0, INT );
	ll_node_set_type( &llist, 1, INT );
	ll_node_set_type( &llist, 2, CSTRING );
	ll_print( llist );
	ll_free( llist );
}

int main()
{
	printf( "~~~ Starting Linked List Tests ~~~\n" );

	test_str_insert();
	test_int_insert();
	test_str_alloc();
	test_delete();
	test_node_type();

	return 0;
}
