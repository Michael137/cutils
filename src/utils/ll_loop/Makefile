include ../../../config.mk

PROJECT=utils
INCLUDES=../../../include
CFLAGS+=-I$(INCLUDES)
CONTAINER_OBJDIR=../../../target/containers
OBJDIR=../../../target/bin
TESTDIR=../../../test/$(PROJECT)

UTILS_OBJDIR=../../../target/utils

_OBJ = linked_list.o linked_list_internal.o linked_list_helpers.o
OBJ = $(patsubst %,$(CONTAINER_OBJDIR)/%,$(_OBJ))

_UTILS_OBJ = ll_loop.o
UTILS_OBJ = $(patsubst %,$(UTILS_OBJDIR)/%,$(_UTILS_OBJ))

$(UTILS_OBJDIR)/ll_loop.o: ll_loop.c
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY: compile_src
compile_src: $(UTILS_OBJ)

test_ll_loop: 
	$(CC) $(TESTDIR)/test_ll_loop.c $(CFLAGS) $(OBJ) $(UTILS_OBJ) -o $(OBJDIR)/test_ll_loop

.PHONY:
clean:
	rm -f $(OBJDIR)/test_ll_loop

test:
	$(OBJDIR)/test_ll_loop

.PHONY: leak
leak:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes $(OBJDIR)/test_ll_loop

all: clean compile_src test_ll_loop test
