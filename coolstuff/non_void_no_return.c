#include <stdbool.h>
#include <stdio.h>

bool false_func() { return false; }
bool true_func() { return true; }

bool test()
{
	false_func();
//	true_func();
}

int main() {
	if(test())
		puts("true");
	return 0;
}
