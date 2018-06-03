CFLAGS=
SANITIZE_FLAGS=

ifneq "$(DEBUG)" ""
  CFLAGS += -DLL_DEBUG
  CFLAGS += -O0 -g
else
  CFLAGS += -O3
endif

ifeq "$(CC)" ""
  CC=gcc
endif

# For strdup() on C11
# CFLAGS += -D_BSD_SOURCE
CFLAGS+=-std=c11
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

# Warnings requires instrumentation
CFLAGS += -Wstrict-aliasing
CFLAGS += -fstrict-aliasing

# Sanitizers
SANITIZE_FLAGS += -fsanitize=undefined
SANITIZE_FLAGS += -fsanitize=address
SANITIZE_FLAGS += -fsanitize=leak
CFLAGS += $(SANITIZE_FLAGS)

# Warnings are errors
CFLAGS += -Werror
CFLAGS += -pedantic-errors
