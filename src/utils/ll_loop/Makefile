PROJECT=utils
INCLUDES=../../../include
CFLAGS+=-I$(INCLUDES)
CONTAINER_OBJDIR=../../../target/containers
OBJDIR=../../../target/bin
TESTDIR=../../../test/$(PROJECT)

_HDRS = linked_list.h linked_list_internal.h linked_list_helpers.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o linked_list_internal.o linked_list_helpers.o
OBJ = $(patsubst %,$(CONTAINER_OBJDIR)/%,$(_OBJ))

test_ll_loop: 
	$(CC) $(TESTDIR)/test_ll_loop.c $(CFLAGS) $(OBJ) -o $(OBJDIR)/test_ll_loop

.PHONY:
clean:
	rm -f $(OBJDIR)/test_ll_loop

test:
	$(OBJDIR)/test_ll_loop

.PHONY: leak
leak:
	valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes $(OBJDIR)/test_ll_loop

all: clean test_ll_loop test
