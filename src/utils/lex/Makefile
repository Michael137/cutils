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

# TODO: cleaner inclusion of other project
OBJ += $(CONTAINER_OBJDIR)/../core/hash.o

# TODO: move makefile to src/utils level and call lex makefile
OBJ += $(UTILS_OBJDIR)/automata.o

$(UTILS_OBJDIR)/automata.o: ../automata.c $(HDRS)
	$(CC) -c $< $(CFLAGS) -o $@

test_fa: test_fa.c
	$(CC) $< $(OBJ) $(CFLAGS) -o $(OBJDIR)/test_fa

.PHONY: compile_src
compile_src: $(UTILS_OBJDIR)/automata.o

.PHONY:
clean:
	rm -f $(OBJDIR)/test_fa

test:
	$(OBJDIR)/test_fa

.PHONY: leak
leak:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_fa

all: clean compile_src test_fa test
