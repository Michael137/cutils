#include <assert.h>
#include <core/hash.h>
#include <stdio.h>

void test_djb2()
{
	assert( hash_str_djb2( "" ) );
	assert( hash_str_djb2( "a" ) != hash_str_djb2( "b" ) );
	assert( hash_str_djb2( "abc" ) != hash_str_djb2( "acb" ) );
	assert( hash_str_djb2( "ab" ) != hash_str_djb2( "ba" ) );
	assert( hash_str_djb2( "23" ) != hash_str_djb2( "32" ) );
	assert( hash_str_djb2( "1" ) != hash_str_djb2( "0" ) );
}

int main()
{
	test_djb2();
	return 0;
}
