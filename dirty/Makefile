all: compile

.PHONY:
compile:
	gcc set.c -lpthread && valgrind --leak-check=full --show-leak-kinds=all ./a.out
