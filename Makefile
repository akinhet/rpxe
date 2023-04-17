VERSION = 2.1

CC = gcc
PREFIX = /usr/local
MANPREFIX = /share/man
CFLAGS = -Wall -lm -lreadline

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
	mkdir -p $(PREFIX)$(MANPREFIX)/man1
	sed "s/VERSION/$(VERSION)/g" < rpxe.1 > $(PREFIX)$(MANPREFIX)/man1/rpxe.1
	chmod 644 $(PREFIX)$(MANPREFIX)/man1/rpxe.1

uninstall:
	rm -f $(PREFIX)/bin/rpxe

.PHONY: clean install uninstall

clean:
	rm -f *.o rpxe
