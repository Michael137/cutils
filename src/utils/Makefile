include ../../config.mk

PROJECT=utils
INCLUDES=../../include
OBJDIR=../../target
CORE_OBJDIR=$(OBJDIR)/core
CONTAINERS_OBJDIR=$(OBJDIR)/containers
PROJ_OBJDIR=$(OBJDIR)/$(PROJECT)
PROJ_TESTDIR=../../test/$(PROJECT)

CFLAGS += -I$(INCLUDES)

_HDRS += automata.h
HDRS = $(patsubst %,$(INCLUDES)/$(PROJECT)/%,$(_HDRS))

_CONT_OBJ = linked_list.o linked_list_internal.o linked_list_helpers.o hashmap.o
OBJ = $(patsubst %,$(CONTAINERS_OBJDIR)/%,$(_CONT_OBJ))

_CORE_OBJ = hash.o
OBJ += $(patsubst %,$(CORE_OBJDIR)/%,$(_CORE_OBJ))

_OBJ = automata.o
OBJ += $(patsubst %,$(PROJ_OBJDIR)/%,$(_OBJ))

$(PROJ_OBJDIR)/%.o: %.c $(HDRS)
	$(CC) -c $< $(CFLAGS) -o $@

.PHONY: compile_src
compile_src: $(OBJ) 

.PHONY: clean
clean:
	rm -f $(PROJ_OBJDIR)/*.o
	rm -f gmon.out

# Tests
test_automata: $(PROJ_TESTDIR)/test_automata.c $(OBJ) $(HDRS)
	$(CC) $^ $(CFLAGS) -o $(PROJ_OBJDIR)/$@

.PHONY:
test:
	$(PROJ_OBJDIR)/test_automata

.PHONY: leak
leak:
	@valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=no --track-origins=yes $(PROJ_OBJDIR)/test_automata

all: clean compile_src test_automata test
