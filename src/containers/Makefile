# Top-level vars
PROJECT=containers
INCLUDES=../../include
CC=gcc
CFLAGS=-std=c11 -I$(INCLUDES)
OBJDIR=../../target/$(PROJECT)

# Headers to include
_HDRS = linked_list.h linked_list_internal.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: %.c $(HDRS)
		$(CC) -c -o $@ $< $(CFLAGS)

all: compile

# Compile but don't link'
.PHONY: compile
compile: $(OBJ) 

# Clean object files
.PHONY: clean
clean:
		rm -f $(OBJDIR)/*.o *~ core $(INCLUDES)/*~		
