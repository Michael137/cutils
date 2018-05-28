PROJECT=utils
INCLUDES=../../include
CFLAGS+=-I$(INCLUDES)
CONTAINER_OBJDIR=../../target/containers
OBJDIR=../../target/$(PROJECT)

_HDRS = linked_list.h linked_list_internal.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o linked_list_internal.o
OBJ = $(patsubst %,$(CONTAINER_OBJDIR)/%,$(_OBJ))

ll_loop: ll_loop.c
	$(CC) $^ $(CFLAGS) $(OBJ) -o ll_loop.o

.PHONY:
clean:
	rm -f ll_loop.o

all: ll_loop clean
