PROJECT=utils
INCLUDES=../../../include
CFLAGS+=-I$(INCLUDES)
CONTAINER_OBJDIR=../../../target/containers
OBJDIR=../../../target/$(PROJECT)

_HDRS = linked_list.h linked_list_internal.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o linked_list_internal.o
OBJ = $(patsubst %,$(CONTAINER_OBJDIR)/%,$(_OBJ))

test_ll_loop: test_ll_loop.c
	$(CC) $^ $(CFLAGS) $(OBJ) -o test_ll_loop.o

.PHONY:
clean:
	rm -f test_ll_loop.o

test:
	./test_ll_loop.o

all: clean test_ll_loop test
