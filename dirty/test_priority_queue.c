#include "priority_queue.h"

#include <stdio.h>

int main() {
	int ints[] = {14, 154, 13, 0, 0, 1000, -40};
	Heap* heap;
	heap_create(&heap, 20);
	for(int i = 0; i < sizeof(ints)/sizeof(ints[0]); ++i)
		heap_insert(heap, (void*)&ints[i], sizeof(ints[0]));
	int ret = *(int*)heap_peek(heap);
	printf("Retrieved: %d\n", ret);
	heap_free(heap);
	return 0;
}
