# Top-level vars
PROJECT=containers
INCLUDES=../../include
CC=gcc
CFLAGS=-std=c11 -I$(INCLUDES)
OBJDIR=../../target/$(PROJECT)
TESTDIR=../../test/$(PROJECT)

ifneq "$(DEBUG_CONTAINERS)" ""
CFLAGS += -DLL_DEBUG
CFLAGS += -O0
else
CFLAGS += -O3
endif

# For strdub on C11
CFLAGS += -D_BSD_SOURCE

# Headers to include
_HDRS = linked_list.h linked_list_internal.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o linked_list_internal.o
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

.PHONY: leak
leak:
		valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes $(OBJDIR)/test_linked_list

all: clean compile_src test_linked_list test
