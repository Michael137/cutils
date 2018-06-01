CFLAGS=

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
CFLAGS += -Werror -Wall --pedantic-errors -Wextra -Wstrict-aliasing -Wshadow -Wpedantic -fstrict-aliasing
