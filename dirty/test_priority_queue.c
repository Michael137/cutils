#include "priority_queue.h"

int main() {
	Heap* heap;
	heap_create(&heap, 20);
	heap_free(heap);
	return 0;
}
