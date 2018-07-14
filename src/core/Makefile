include ../../config.mk

# Top-level vars
PROJECT=core
INCLUDES=../../include

CFLAGS+=-I$(INCLUDES)
OBJDIR=../../target/$(PROJECT)
TESTDIR=../../test/$(PROJECT)

# Headers to include
_HDRS = hash.h
# Prepend include path to every header
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_OBJ = hash.o
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
	rm -f $(OBJDIR)/test_hash
	rm -f gmon.out
	rm -f *.gcno
	rm -f *.gcda

# Tests
test_hash: $(TESTDIR)/test_hash.c $(OBJ) $(HDRS)
	$(CC) $^ $(CFLAGS) -o $(OBJDIR)/$@

.PHONY: test
test:
	$(OBJDIR)/test_hash

# TODO: move to separate script taking test name as argument
.PHONY: leak
leak:
	@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(OBJDIR)/test_hash

all: clean compile_src test_hash test
