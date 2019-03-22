#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

static void swap(void** a, void** b, int size)
{
	unsigned char *p = *a,
				  * q = *b,
				  tmp;
	for (int i = 0; i != size; ++i)
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
	printf("%d %d\n", *(int*)a,*(int*)b);
	return *(int*)a > *(int*)b;
}

int heap_create(Heap** heap, int size)
{
	if(heap)
	{
		(*heap) = malloc(sizeof(Heap));
		(*heap)->items = malloc(size * sizeof(void*));
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
		printf("Deleting %d elements\n", heap->elements);
		free(heap->items);
		free(heap);
		heap = NULL;
	}
}

/*
 * Insert at farthest level from root
 * While new node is not at the top
 * 		bubble up the node until the heap property is satisfied
 */
int heap_insert(Heap* heap, void* key, int size)
{
	assert(heap->elements < heap->capacity);
	int idx = (heap->elements == 0) ? 0 : heap->elements;
	heap->items[idx] = key;
	int parent = 0;
	printf( "Inserting: %d %d (idx) %d (parent)\n", *(int*)key, idx, parent);
	while(idx != 0)
	{
		parent = PARENT(idx);
		if(heap->cmp_fn(heap->items[idx], heap->items[parent]))
		{
			puts("SWAPPING");
			swap(&(heap->items[idx]), &(heap->items[parent]), size);
			idx = parent;
		} else
			break;
	}

	printf("Final idx: %d\n", idx);
	heap->elements++;

	return PQ_OK;
}

void* heap_peek(Heap* heap)
{
	if(heap->elements > 0) {
		printf("Retrieved: %p\n", heap->items[0]);
		return heap->items[0];
	} else {
		return NULL;
	}
}
