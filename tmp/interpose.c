// gcc -shared -ldl -fPIC interpose.c -o interpose.so

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdint.h>
#include <stdio.h>

void* malloc( size_t size )
{
	static void* ( *real_malloc )( size_t ) = NULL;
	if( !real_malloc ) real_malloc = dlsym( RTLD_NEXT, "malloc" );

	void* p = real_malloc( size );
	if( p ) printf( "malloc(%d) = %p\n", size, p );
	return p;
}
