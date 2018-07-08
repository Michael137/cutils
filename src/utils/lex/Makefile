include ../../../config.mk

PROJECT=utils
INCLUDES=../../../include
CFLAGS+=-I$(INCLUDES)
CONTAINER_OBJDIR=../../../target/containers
OBJDIR=../../../target/bin
TESTDIR=../../../test/$(PROJECT)

UTILS_OBJDIR=../../../target/utils

_OBJ = linked_list.o linked_list_internal.o linked_list_helpers.o
_OBJ += hashmap.o
OBJ = $(patsubst %,$(CONTAINER_OBJDIR)/%,$(_OBJ))

test_dfa: dfa.c
	$(CC) $< $(OBJ) $(CFLAGS) -o $(OBJDIR)/test_dfa

.PHONY:
clean:
	rm -f $(OBJDIR)/test_dfa

test:
	$(OBJDIR)/test_dfa

.PHONY: leak
leak:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_dfa

all: clean test_dfa test
