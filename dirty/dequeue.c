// Double-ended queue implemented
// using a circular buffer

#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DQ_FULL( dq_ ) ( dq->elements == dq->capacity )
#define DQ_EMPTY( dq_ ) ( dq->elements == 0 )

#define dequeue_init( type, name, size )                                       \
	typedef struct                                                             \
	{                                                                          \
		size_t capacity;                                                       \
		size_t elements;                                                       \
		size_t head;                                                           \
		type* data;                                                            \
	} dequeue_##type

typedef struct
{
	size_t capacity; // Maximum size buffer can reach
	size_t elements; // Current number of valid elements
	size_t head;     // Index of start to currently valid data
	void** data;     // Contents of buffer
} Dequeue;

Dequeue* dq_create( size_t size )
{
	assert( size > 0 );
	Dequeue* dq = malloc( sizeof( Dequeue ) );
	if( dq )
	{
		dq->data = malloc( sizeof( void* ) * size );
		if( dq->data == NULL )
		{
			free( dq );
			dq = NULL;
			return NULL;
		}
		dq->elements = 0;
		dq->head     = -1;
		dq->capacity = size;
		return dq;
	}
	else
	{
		return NULL;
	}
}

void enqueue( Dequeue* dq, void* item )
{
	assert( dq != NULL );
	dq->head++;
	dq->data[dq->head] = item;
	dq->elements++;
}

void* dequeue( Dequeue* dq )
{
	assert( dq != NULL );
	assert( !DQ_EMPTY( dq ) );
	assert( dq->head < dq->elements );
	void* item = dq->data[dq->head];
	dq->head--;
	dq->elements--;
	return item;
}

void dq_free( Dequeue* dq )
{
	if( dq )
	{
		free( dq->data );
		free( dq );
		dq = NULL;
	}
}

int main()
{
	Dequeue* dq = dq_create( 1024 );
	int x = 5;
	int y = 6;
	enqueue( dq, (void*)&x );
	enqueue( dq, (void*)&y );
	printf( "%d\n", *(int*)dequeue( dq ) );
	dq_free( dq );
	return 0;
}
