CC = gcc
PREFIX = /usr/local
CFLAGS = -Wall -lm

DEPS = stack.h

OBJ = rpxe.o stack.o

rpxe: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

install: rpxe
	mkdir -p $(PREFIX)/bin
	cp -f rpxe $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/rpxe

uninstall:
	rm -f $(PREFIX)/bin/rpxe

.PHONY: clean

clean:
	rm -f *.o rpxe
