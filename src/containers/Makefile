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
_TESTOBJ = test_linked_list.o
TESTOBJ = $(patsubst %,$(OBJDIR)/%,$(_TESTOBJ))

$(OBJDIR)/%.o: $(TESTDIR)/%.c $(HDRS)
		$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: compile_tests
compile_tests: $(TESTOBJ) $(OBJ)
		$(CC) $< -o $(OBJDIR)/$@

.PHONY: test
		$(shell exec $(OBJDIR)/test_linked_list)

all: compile_src compile_tests test
