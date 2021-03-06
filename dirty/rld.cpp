// Run-length decode a string

#include <assert.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

#define IS_NUM( c ) ( ( c ) >= '0' && ( c ) <= '9' )
#define REP_IF_EMPTY( str ) ( ( str.empty() ) ? "<Empty string>" : str )

std::string rld( std::string const& str )
{
	if( str.length() == 0 )
		return "";

	std::string iss;
	std::string cur_num;
	std::string cur_word;
	int cur_brkt_loc = 0;
	for( int i = 0; i < str.length() - 1; ++i )
	{
		if( IS_NUM( str[i] ) )
		{
			cur_num += str[i];
			if( str[i + 1] == '[' )
			{
				for( int j = i + 2; j < str.length(); ++j )
				{
					if( str[j] == ']' )
					{
						for( int k = 0; k < std::stoi( cur_num, nullptr ); ++k )
							iss += cur_word;
						cur_num      = "";
						cur_word     = "";
						cur_brkt_loc = j;
						break;
					}
					cur_word += str[j];
				}
				i = cur_brkt_loc;
			}
		}
		else
		{
			if( cur_num != "" )
			{
				iss += cur_num;
				cur_num = "";
			}
			iss += str[i];
		}
	}

	if( cur_num != "" )
		iss += cur_num;

	if( str.back() != ']' || cur_brkt_loc != str.length() - 1 )
		iss += str.back();

	return iss;
}

static int assertions_run = 0;
void end_tests()
{
	std::cout << "## " << assertions_run << " assertions run" << std::endl;
}

void test( std::string const& str, std::string const& expected )
{
	auto rldd = rld( str );
	std::cout << REP_IF_EMPTY( str ) << '\n'
	          << "\t-> " << REP_IF_EMPTY( rldd ) << std::endl;
	assert( rldd == expected );
	assertions_run++;
}

int main( int argc, char* argv[] )
{
	test( "String3[01]", "String010101" );
	test( "String3[1]", "String111" );
	test( "String0[1]", "String" );
	test( "String5[a]", "Stringaaaaa" );
	test( "a1[b]", "ab" );
	test( "5[a]", "aaaaa" );
	test( "", "" );
	test( "12345a12345", "12345a12345" );
	test( "String5[a]ab", "Stringaaaaaab" );
	test( "String5[a]2ab", "Stringaaaaa2ab" );
	test( "String5[a][ab]", "Stringaaaaa[ab]" );
	test( "String5[a]2[cd]10", "Stringaaaaacdcd10" );
	end_tests();
	return 0;
}
