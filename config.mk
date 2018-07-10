CFLAGS=
SANITIZE_FLAGS=

ifneq "$(DEBUG)" ""
  CFLAGS += -DLL_DEBUG=1
  CFLAGS += -DHM_DEBUG=1
  CFLAGS += -O0 -g
else
  CFLAGS += -DLL_DEBUG=0
  CFLAGS += -DHM_DEBUG=0
  CFLAGS += -O3
endif

ifeq "$(CC)" ""
  CC=gcc
endif

# For strdup() on C11
# CFLAGS += -D_BSD_SOURCE
CFLAGS += -std=c11
CFLAGS += -D_DEFAULT_SOURCE

# Base warnings
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wpedantic

# Additional useful warnings
CFLAGS += -Wshadow
CFLAGS += -Wnull-dereference
CFLAGS += -Wunknown-pragmas
CFLAGS += -Winline
CFLAGS += -Wnull-dereference

# Warnings requires instrumentation
CFLAGS += -Wstrict-aliasing
CFLAGS += -fstrict-aliasing

# Sanitizers
ifneq "$(DEBUG)" ""
  SANITIZE_FLAGS += -fsanitize=undefined
  SANITIZE_FLAGS += -fsanitize=address
  SANITIZE_FLAGS += -fsanitize=leak
  CFLAGS += $(SANITIZE_FLAGS)
endif

# Warnings are errors
CFLAGS += -Werror
CFLAGS += -pedantic-errors

# TODO: enable flags on per-target basis
# Instrumentation
ifneq "$(COVERAGE)" ""
  CFLAGS += -fprofile-arcs -ftest-coverage
endif

ifneq "$(PROFILE)" ""
  # gprof profiling
  CFLAGS += -pg
  CFLAGS += -finstrument-functions
endif
