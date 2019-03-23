all: compile

.PHONY:
compile:
	gcc -DCOARSE_LOCK set.c -lpthread && valgrind --leak-check=full --show-leak-kinds=all ./a.out
	#gcc -DFINE_LOCK set.c -lpthread && valgrind --leak-check=full --show-leak-kinds=all ./a.out
