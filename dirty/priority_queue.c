#include "priority_queue.h"
#include <stdlib.h>

static void swap(void** a, void** b, int size)
{
	unsigned char *p = *a,
				  * q = *b,
				  * tmp;
	for (size_t i = 0; i != size; ++i)
	{
		tmp = p[i];
		p[i] = q[i];
		q[i] = tmp;
	}
}

static int heapify(Heap* heap, int idx, int size, int item_size)
{
	int largest = idx;
	int left = PQ_LEFT(idx);
	int right = PQ_RIGHT(idx);

	if(left < size && heap->cmp_fn(heap->items[left], heap->items[largest]))
		largest = left;
	if(right < size && heap->cmp_fn(heap->items[right], heap->items[largest]))
		largest = right;

	if(largest != idx)
	{
		swap(&(heap->items[idx]),&(heap->items[largest]), item_size);
		heapify(heap, largest, size, item_size);
	}
	return PQ_OK;
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
