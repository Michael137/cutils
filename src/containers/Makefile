# Top-level vars
PROJECT=containers
INCLUDES=../../include
CC=gcc
CFLAGS=-std=c11 -I$(INCLUDES)
OBJDIR=../../target/$(PROJECT)
TESTDIR=../../test/$(PROJECT)

ifneq "$(DEBUG_CONTAINERS)" ""
CFLAGS += -DLL_DEBUG
endif

# Headers to include
_HDRS = linked_list.h linked_list_internal.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: %.c $(HDRS)
		$(CC) -c -o $@ $< $(CFLAGS)

# Compile but don't link'
.PHONY: compile_src
compile_src: $(OBJ) 

# Clean object files
.PHONY: clean
clean:
		rm -f $(OBJDIR)/*.o *~ core $(INCLUDES)/*~

# Tests
test_linked_list: $(TESTDIR)/*.c $(OBJ) $(HDRS)
		$(CC) -o $(OBJDIR)/$@ $^ $(CFLAGS)

.PHONY: test
test:
		$(OBJDIR)/test_linked_list

all: compile_src test_linked_list test
