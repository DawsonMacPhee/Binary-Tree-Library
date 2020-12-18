CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: tree.o

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c -o tree.o

clean:
	rm tree.o