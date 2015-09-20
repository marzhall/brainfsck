CC     = gcc
CFLAGS = -g -I.
DEPS   = bf.h
BUILDDIR = bin

bfi: bf.o
	$(CC) -o $(BUILDDIR)/bfi bf.o $(CFLAGS)

clean:
	rm *.o
	rm bin/*
