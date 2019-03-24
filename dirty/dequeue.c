// Double-ended queue implemented
// using a circular buffer

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Full if write pointer is one slot behind the read pointer
#define DQ_FULL( circ_ ) ( circ_->readp == ( ( circ_->writep + 1 ) % circ_->capacity ) )
#define DQ_EMPTY( circ_ ) ( circ_->readp == circ_->writep )

typedef struct
{
	size_t capacity; // Maximum size buffer can reach
	size_t readp;
	size_t writep;
	void** data; // Contents of buffer
} CircBuf;

CircBuf* circ_create( size_t size )
{
	assert( size > 0 );
	CircBuf* crc = malloc( sizeof( CircBuf ) );
	if( crc )
	{
		crc->data = malloc( sizeof( void* ) * size );
		if( crc->data == NULL )
		{
			free( crc );
			crc = NULL;
			return NULL;
		}
		crc->writep   = 0;
		crc->readp    = 0;
		crc->capacity = size + 1;
		return crc;
	}
	else
	{
		return NULL;
	}
}

void* circ_read( CircBuf* crc )
{
	assert( crc != NULL );
	assert( !( DQ_EMPTY( crc ) ) );
	void* ret = crc->data[crc->readp];
	crc->readp = ( crc->readp + 1 ) % crc->capacity;
	return ret;
}

void circ_write( CircBuf* crc, void* item )
{
	assert( crc != NULL );
	assert( !DQ_FULL( crc ) );
	crc->data[crc->writep] = item;
	crc->writep           = ( crc->writep + 1 ) % crc->capacity;
}

void circ_free( CircBuf* crc )
{
	if( crc )
	{
		free( crc->data );
		free( crc );
		crc = NULL;
	}
}

int main()
{
	CircBuf* crc = circ_create( 8 );
	for(int i = 0; i < 32; ++i)
	{
		circ_write( crc, (void*)&i );
		printf( "%d %d %d\n", *(int*)circ_read( crc ), crc->writep, crc->readp );
	}
	circ_free( crc );
	return 0;
}
