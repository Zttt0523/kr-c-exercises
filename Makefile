CC      = gcc
CFLAGS  = -std=c17 -Wall -Wextra -pedantic -g
BINDIR  = bin

# 自动发现所有 .c 文件，生成 bin/ 下的目标
SRCS    = $(shell find . -name '*.c')
TARGETS = $(patsubst ./%.c,$(BINDIR)/%,$(SRCS))

.PHONY: all clean

all: $(TARGETS)

$(BINDIR)/%: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf $(BINDIR)
