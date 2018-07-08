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

test_fa: test_fa.c
	$(CC) $< $(OBJ) $(CFLAGS) -o $(OBJDIR)/test_fa

.PHONY:
clean:
	rm -f $(OBJDIR)/test_fa

test:
	$(OBJDIR)/test_fa

.PHONY: leak
leak:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_fa

all: clean test_fa test
