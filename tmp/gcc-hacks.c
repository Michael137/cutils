#include <stdio.h>
#include <stdlib.h>

struct myStruct
{
	int a;
	int b;
};

static int case_hack( int idx )
{
	switch( idx ) {
	case 0:
		puts( "0" );
		break;
	case 1 ... 7:
		puts( "1...7" );
		break;
	case 8 ... 15:
		puts( "8...15" );
		break;
	default:
		return 0;
	}
}

int arr[] = {[0 ... 5] = 1, [7 ... 9] = 2, [15] = 3};

int main()
{
	case_hack( 1 );
	case_hack( 5 );
	case_hack( 12 );
	case_hack( 15 );
	case_hack( 16 );

	for( int i = 0; i < sizeof( arr ) / sizeof( arr[0] ); ++i )
		printf( "%d", arr[i] );
	return 0;
}
