CC      = gcc
CFLAGS  = -std=c17 -Wall -Wextra -pedantic -g
TARGETS = ch01-tutorial-introduction/hello \
          ch02-types-operators-expressions/example \
          ch03-control-flow/example \
          ch04-functions-program-structure/example \
          ch05-pointers-and-arrays/example \
          ch06-structures/example \
          ch07-input-and-output/example \
          ch08-unix-system-interface/example

.PHONY: all clean $(TARGETS)

all: $(TARGETS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	find . -type f -executable -delete
	find . -name "*.o" -delete
