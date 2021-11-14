CC=gcc
CFLAGS = -Wall -lm

DEPS = stack.h

OBJ = expr.o stack.o

expr: $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm *.o expr
