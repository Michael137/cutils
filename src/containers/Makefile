include ../../config.mk

# Top-level vars
PROJECT=containers
INCLUDES=../../include

CFLAGS+=-I$(INCLUDES)
OBJDIR=../../target/$(PROJECT)
TESTDIR=../../test/$(PROJECT)

# Headers to include
_HDRS = linked_list.h linked_list_internal.h linked_list_helpers.h
_HDRS += hashmap.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o linked_list_internal.o linked_list_helpers.o
_OBJ += hashmap.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

$(OBJDIR)/%.o: %.c $(HDRS)
		$(CC) -c $< $(CFLAGS) -o $@ 

# Compile but don't link'
.PHONY: compile_src
compile_src: $(OBJ) 

# Clean object files
.PHONY: clean
clean:
		rm -f $(OBJDIR)/*.o *~ core $(INCLUDES)/*~ \
		rm -f $(OBJDIR)/test_linked_list

# Tests
test_linked_list: $(TESTDIR)/*.c $(OBJ) $(HDRS)
		$(CC) $^ $(CFLAGS) -o $(OBJDIR)/$@ 

.PHONY: test
test:
		$(OBJDIR)/test_linked_list

.PHONY: leak
leak:
		valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes --track-origins=yes $(OBJDIR)/test_linked_list

all: clean compile_src test_linked_list test
