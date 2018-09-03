include ../../config.mk

# TODO: for all projs create .so to reduce makefile clutter
#       and remove static linking

# Top-level vars
PROJECT=containers
INCLUDES=../../include

CFLAGS+=-I$(INCLUDES)
OBJDIR=../../target/$(PROJECT)
TESTDIR=../../test/$(PROJECT)

# TODO: split linked list and hashmap targets
#       and compile/link stages
# Headers to include
_HDRS = linked_list.h linked_list_internal.h linked_list_helpers.h
_HDRS += hashmap.h
_HDRS += nary_tree.h
_HDRS += trie.h trie_internals.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = linked_list.o linked_list_internal.o linked_list_helpers.o
_OBJ += hashmap.o
_OBJ += nary_tree.o
_OBJ += trie.o trie_internals.o
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

# TODO: cleaner inclusion of other project
OBJ += $(OBJDIR)/../core/hash.o

$(OBJDIR)/%.o: %.c $(HDRS)
	$(CC) -c $< $(CFLAGS) -o $@

# Compile but don't link'
.PHONY: compile_src
compile_src: $(OBJ) 

# Clean object files
.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLUDES)/*~ \
	rm -f $(OBJDIR)/test_linked_list \
	rm -f $(OBJDIR)/test_hashmap
	rm -f $(OBJDIR)/test_nary_tree \
	rm -f $(OBJDIR)/test_trie \
	rm -f gmon.out
	rm -f *.gcno
	rm -f *.gcda

# Tests
test_linked_list: $(TESTDIR)/test_linked_list.c $(OBJ) $(HDRS)
	$(CC) $^ $(CFLAGS) -o $(OBJDIR)/$@

# TODO: cleaner externals inclusion
test_hashmap: $(TESTDIR)/test_hashmap.c $(OBJ) $(HDRS)
	$(CC) $^ $(CFLAGS) -o $(OBJDIR)/$@ -lgsl -lgslcblas -lm

test_nary_tree: $(TESTDIR)/test_nary_tree.c $(OBJ) $(HDRS)
	$(CC) $^ $(CFLAGS) -o $(OBJDIR)/$@

test_trie: $(TESTDIR)/test_trie.c $(OBJ) $(HDRS)
	$(CC) $^ $(CFLAGS) -o $(OBJDIR)/$@

.PHONY:
test:
	$(OBJDIR)/test_linked_list
	$(OBJDIR)/test_hashmap
	$(OBJDIR)/test_nary_tree
	$(OBJDIR)/test_trie

# TODO: move to separate script taking test name as argument
.PHONY: leak
leak:
	-@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_linked_list
	-@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_hashmap
	-@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_nary_tree
	-@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_trie

all: clean compile_src test_linked_list test_hashmap test_nary_tree test test_trie
