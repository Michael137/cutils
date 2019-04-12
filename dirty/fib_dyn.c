// Fibonacci that handles overflow up until
// numbers representable using an
// unsigned long long

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

#define PHI 1.61803399

// Using Binet's formula for the
// nth Fibonacci number (and approximating
// for large values of Fibonacci to drop
// the phi^-n term) find the largest
// representable Fibonacci number up
// to a given number
#define LARGEST_FIB( type )                                                    \
	( (int)( ( log2l( type ) + log2l( sqrt( 5 ) ) ) / log2l( PHI ) ) )

typedef unsigned long long ULL;

ULL fib( int n )
{
	ULL tbl[LARGEST_FIB( ULLONG_MAX )];
	tbl[0] = 0;
	tbl[1] = 1;
	tbl[2] = 1;
	for( int i = 2; i <= n; ++i )
	{
		if( ULLONG_MAX - tbl[i - 2] < tbl[i - 1] )
		{
			printf( "Overflow caused at '%d'", i );
			abort();
		}
		tbl[i] = tbl[i - 2] + tbl[i - 1];
	}
	return tbl[n];
}

int last_fib_digit( int num ) {
	ULL fib_ret = fib(num);
	return (fib_ret < 10) ? fib_ret : fib_ret % 10;
}

int main()
{
	printf( "%llu\n", fib( 93 ) );
	printf( "%d\n", last_fib_digit( 93 ) );
	printf( "%llu\n", fib( 2 ) );
	printf( "%d\n", last_fib_digit( 2 ) );
	printf( "%llu\n", fib( 94 ) );
	return 0;
}
