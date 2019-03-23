// Herlihy & Shavit Chapter 9 Concurrent Sets

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct Node {
	struct Node* next;
	struct Node* prev;
	int data;
	// size_t key; // (UNUSED) Hash code of item
} Node;

typedef struct {
	struct Node* head;
	struct Node* tail;
	size_t elements;
	pthread_mutex_t coarse_lock;
} Set;

Set* set_create()
{
	Set* s = malloc(sizeof(Set));
	if(s == NULL)
		return NULL;
	s->head = NULL;
	s->tail = NULL;
	s->elements = 0;
	pthread_mutex_init( &s->coarse_lock, NULL );
	return s;
}

void set_free(Set* s)
{
	if(s)
	{
		Node* it = s->head;
		Node* del = NULL;
		while(it != NULL)
		{
			del = it;
			it = it->next;
			free(del);
		}
		free(s);
		s = NULL;
	}
}

bool set_contains(Set* set, int item)
{
	if(set == NULL)
		return false;
	Node* it = set->head;
	while(it != NULL)
	{
		if(it->data == item)
			return true;
		it = it->next;
	}
	return false;
}

bool add_head(Set* set, int item)
{
	if(set == NULL)
		return false;
	Node* new_node = malloc(sizeof(Node));
	if(new_node == NULL)
		return false;
	new_node->data = item;
	new_node->next = set->head;
	new_node->prev = NULL;
	if(set->head != NULL)
		set->head->prev = new_node;
	set->head = new_node;
	return true;
}

bool add_tail(Set* set, int item)
{
	if(set == NULL)
		return false;
	Node* new_node = malloc(sizeof(Node));
	if(new_node == NULL)
		return false;
	new_node->data = item;
	new_node->prev = set->tail;
	new_node->next = NULL;
	set->tail->next = new_node;
	set->tail = new_node;
	return true;
}

// Concurrent insertion
bool set_add(Set* set, int item)
{
	if(set == NULL)
		return false;
	pthread_mutex_lock(&set->coarse_lock);

	if(set->elements == 0)
	{
		add_head(set, item);
		set->tail = set->head;
		goto success;
	}

	if(set->elements == 1)
	{
		if(set->head->data == item)
			goto error;
		else if(set->head->data < item)
			add_tail(set, item);
		else
			add_head(set, item);
		goto success;
	}

	Node* pred;
	Node* curr;
	pred = set->head;
	curr = pred->next;
	while(curr != NULL && curr->data < item)
	{
		pred = curr;
		curr = curr->next;
	}

	if(curr == NULL){
		// Key is greater than all elements in set
		add_tail(set, item);
		goto success;
	} else if(item == curr->data || item == pred->data) {
		// Key already exists
		goto error;
	} else {
		// Insert before iterator
		Node* new_node = malloc(sizeof(Node));
		if(new_node == NULL)
			goto error;
		new_node->data = item;
		curr->prev = new_node;
		new_node->next = curr;
		new_node->prev = pred;
		pred->next = new_node;
		goto success;
	}

error:
	pthread_mutex_unlock(&set->coarse_lock);
	return false;

success:
	set->elements++;
	pthread_mutex_unlock(&set->coarse_lock);
	return true;
}

bool set_remove(Set* set, int item)
{
	if(set == NULL || set->elements == 0)
		return false;
	pthread_mutex_lock(&set->coarse_lock);

	if(set->elements == 1)
	{
		if(set->head->data != item)
			goto error;
		else
		{
			free(set->head);
			set->head = NULL;
			set->tail = NULL;
			goto success;
		}
	}

	Node* pred;
	Node* curr;
	pred = set->head;
	curr = pred->next;
	while(curr != NULL && curr->data < item)
	{
		pred = curr;
		curr = curr->next;
	}

	if(curr == NULL || (item != curr->data && item != pred->data)){
		// No key found
		goto error;
	} else {
		pred->next = curr->next;
		if(curr->next != NULL)
			curr->next->prev = pred;
		free(curr);
		goto success;
	}

error:
	pthread_mutex_unlock(&set->coarse_lock);
	return false;

success:
	set->elements--;
	pthread_mutex_unlock(&set->coarse_lock);
	return true;
}

/* Test routines */
typedef struct {
	Set* set;
	int num;
} thread_arg;

void* thread_fn(void* arg)
{
	thread_arg* ta = arg;
	for(int i = 0; i < ta->num; ++i)
		set_add(ta->set, i);
	pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
	thread_arg thread_arg1, thread_arg2;

	Set* s = set_create();

	thread_arg1.set = s;
	thread_arg1.num = 7;

	thread_arg2.set = s;
	thread_arg2.num = 14;

	pthread_t t1;
	pthread_t t2;
	pthread_create(&t1, NULL, thread_fn, &thread_arg1);
	pthread_create(&t2, NULL, thread_fn, &thread_arg2);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	Node* it = s->head;
	while(it != NULL)
	{
		printf( "%d ", it->data );
		it = it->next;
	}
	printf("%d\n", s->elements);
	set_free(s);
	return 0;
}
