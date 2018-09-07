#include "heap.h"
#include <iostream>

int main()
{
	std::vector<int> vec{1, 4, 9, -2, 3};
	MaxHeap<int> maxHeap{vec};
	for( auto e : maxHeap )
		std::cout << e << std::endl;

	MinHeap<int> minHeap{vec};
	for( auto e : minHeap )
		std::cout << e << std::endl;

	return 0;
}
