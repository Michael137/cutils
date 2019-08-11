#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
	char buf[1024];
	puts("Enter string");
	scanf("%s", buf);
	int i = 0;
	for(char* p = buf; *p != '\0'; ++p,++i) {
		printf("%c\t%d\n", buf[i], i+1);
		puts("#--------#");
	}

	char req[1024];
	size_t idx = 0;
	size_t len = strlen(buf);
	while(1) {
		scanf("%s", req);
		idx = atoi(req);
		if(idx > 0 && idx <= len)
			printf("#--------#\n%c\t%ld\n", buf[idx - 1], idx);
		else
			printf("WARNING: please enter valid index (1-%ld)\n", len);
	}

	return 0;
}
