// https://wiki.sei.cmu.edu/confluence/display/c/PRE30-C.+Do+not+create+a+universal+character+name+through+concatenation

#include <stdio.h>

#define assign_safe( ucn, val ) ucn = val

void func( void )
{
	int \u0401;

	assign_safe( \u0401, 4 );
	printf( "%d\n", \u0401 );
}

int main() { func(); }
