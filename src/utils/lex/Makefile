include ../../../config.mk

PROJECT=utils
INCLUDES=../../../include
CFLAGS+=-I$(INCLUDES)
CONTAINER_OBJDIR=../../../target/containers
OBJDIR=../../../target/bin
TESTDIR=../../../test/$(PROJECT)

UTILS_OBJDIR=../../../target/utils

_OBJ += hashmap.o
OBJ = $(patsubst %,$(CONTAINER_OBJDIR)/%,$(_OBJ))

_UTILS_OBJ = dfa.o
UTILS_OBJ = $(patsubst %,$(UTILS_OBJDIR)/%,$(_UTILS_OBJ))

$(UTILS_OBJDIR)/dfa.o: dfa.c
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY: compile_src
compile_src: $(UTILS_OBJ)

.PHONY:
clean:
	rm -f $(OBJDIR)/test_dfa

test:
	$(OBJDIR)/test_dfa

.PHONY: leak
leak:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes $(OBJDIR)/test_dfa

all: clean compile_src test_dfa test
