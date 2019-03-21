#include "priority_queue.h"
#include <stdlib.h>


int heapify(Heap* heap, int key)
{
	return PQ_ERR;
}

int heap_cmp_fn_default(void* a, void* b)
{
	return *(int*)a == *(int*)b;
}

int heap_create(Heap** heap, int size)
{
	if(heap)
	{
		(*heap) = malloc(sizeof(Heap));
		(*heap)->items = malloc(sizeof(void*) * size);
		(*heap)->capacity = size;
		(*heap)->elements = 0;
		(*heap)->cmp_fn = heap_cmp_fn_default;
		return PQ_OK;
	}

	return PQ_ERR;
}

void heap_free(Heap* heap)
{
	if(heap)
	{
		free(heap->items);
		free(heap);
		heap = NULL;
	}
}
