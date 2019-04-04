#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#ifndef MIN
#define MIN(a,b) ((a<b)?(a):(b))
#endif

int transfer(int arr[], size_t from, size_t to, size_t amount)
{
	//printf( "transfer: %ld %ld (%ld)\n", from, to, amount );
	assert(arr[from] >= amount);
	assert(amount >= 0);
	arr[from] -= amount;
	arr[to] += amount;
}

void zero_list(int arr[], size_t size)
{
	if(size == 0 || size == 1)
		return;

	size_t p1 = 0, // Always +ve
		   p2 = 0; // Always -ve
	while(p1 < size && p2 < size)
	{
		while(arr[p1] <= 0 && p1 < size)
			p1++;
		while(arr[p2] >= 0 && p2 < size)
			p2++;

		if(p1 == size || p2 == size)
			break;
		transfer(arr, p1, p2, MIN(abs(arr[p1]), abs(arr[p2])));
	}
}

int main() {
	int arr[] = {0, 1, 2, 3, -4, -1, -1, -1, -1, -2, 4};
	size_t len = sizeof(arr)/ sizeof(arr[0]);
	printf("%ld\n", len);
	for(int i = 0; i < len; ++i)
		printf("%d ", arr[i]);
	puts("");
	zero_list(arr, sizeof(arr)/ sizeof(arr[0]));
	for(int i = 0; i < len; ++i)
		printf("%d ", arr[i]);
	puts("");
	return 0;
}
