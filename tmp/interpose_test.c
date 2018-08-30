// gcc interpose_test.c interpose.so -o interpose

#include <stdlib.h>
#include <stdio.h>

int main()
{
	char* arr = malloc( sizeof( char ) * 25 );
	if( arr ) puts( "malloced" );

	free( arr );
	return 0;
}
