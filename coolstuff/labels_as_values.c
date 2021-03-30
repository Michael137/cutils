#include <stdio.h>

int main() {
	static void *lbls[] = {&&start, &&inc, &&end};
	int x = 0,
		y = 10;
	goto *lbls[0];

inc:
	x++;
	goto *lbls[0];

start:
	if(x >= y)
		goto *lbls[2];
	printf("%p %p %p\n", &&inc, &&start, &&end);
	goto *lbls[1];

end:
	return 0;
}
