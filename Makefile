CC ?= clang
CFLAGS ?= -g -Wall -Werror -pedantic -std=c99

SRCS = cpuid.c test.c
OBJS = $(patsubst %.c,%.o,$(SRCS))
DEPS = $(patsubst %.c,%.d,$(SRCS))

all: test

-include $(DEPS)

test: $(OBJS)
	$(CC) -g $? -o $@

%.o: %.c Makefile
	$(CC) -MD -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.d *.o test

.PHONY: clean
