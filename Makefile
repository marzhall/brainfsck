CC     = gcc
CFLAGS = -g -I.
DEPS   = bf.h

bfi: bf.o
	$(CC) -o bfi bf.o $(CFLAGS)

clean:
	rm bfi *.o
