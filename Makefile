CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: tree.o ttest

tree.o: tree.c
	$(CC) $(CFLAGS) -c tree.c -o tree.o

ttest.o: ttest.c
	$(CC) $(CFLAGS) -c ttest.c -o ttest.o

ttest: tree.o ttest.o
	$(CC) $(CFLAGS) tree.o ttest.o -o ttest

clean:
	rm tree.o ttest.o ttest