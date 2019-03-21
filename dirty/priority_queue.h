#ifndef PRIO_QUEUE_H_IN
#define PRIO_QUEUE_H_IN

#include <math.h>

enum {
	PQ_OK = 0,
	PQ_ERR
};

typedef struct {
	void** items;
	int capacity;
	int elements;
	int (*cmp_fn)(void*, void*);
} Heap;

#define PQ_LEFT(idx_) (idx_ * 2 + 1)
#define PQ_RIGHT(idx_) (idx_ * 2 + 2)
#define PARENT(idx_) (idx_ / 2)

int heap_insert(Heap* heap, int key, int size);
int heap_remove(Heap* heap, int key);
int heap_find(Heap* heap, int key);
int heap_peek(Heap* heap);
int heap_cmp_fn_default(void*, void*);
int heap_create(Heap** heap, int size);
void heap_free(Heap* heap);

#endif // PRIO_QUEUE_H_IN
