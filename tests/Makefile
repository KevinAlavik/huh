CC = gcc
CFLAGS = -I ../include/
SRC = $(wildcard *.c)
OUT = $(patsubst %.c,%,$(SRC))

test: $(OUT)
	@for test in $(OUT); do \
		./$$test; \
		rm -f $$test; \
	done

$(OUT): %: %.c
	@$(CC) $(CFLAGS) -o $@ $<

.PHONY: test
