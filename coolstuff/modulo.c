// https://en.wikipedia.org/wiki/Modulo_operation#Performance_issues

#include <stdio.h>
#include <stdlib.h>

int main()
{
	div_t res_div = div( 1423, 16 );
	int res_slow = 1423 % 16;
	int res_fast = 1423 & ( 15 );

	printf( "%d %d %d", res_div.rem, res_slow, res_fast );

	return 0;
}
