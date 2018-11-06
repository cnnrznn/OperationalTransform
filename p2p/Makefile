src=$(wildcard *.c)
obj=$(src:.c=.o)

all: docs

docs: $(obj)
	gcc -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) docs
