// Top-level vars
PROJECT=containers
INCLUDES=include/$(PROJECT)
CC=gcc
CFLAGS=-I$(INCLUDES)
OBJDIR=target/$(PROJECT)

// Headers to include
_HDRS = linked_list.h linked_list_internal.h
// Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/%,$(_HDRS))

_OBJ = linked_list.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: %.c $(HDRS)
		$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
		rm -f $(OBJDIR)/*.o *~ core $(INCLUDES)/*~		
