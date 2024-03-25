# CFLAGS=-Wall -g
CFLAGS=-Wall -g -fsanitize=address -fno-omit-frame-pointer

all: vector_test llist_test

vector.o: vector.c
llist.o: llist.c

vector_test: vector_test.c vector.o
llist_test: llist_test.c llist.o

clean:
	rm ./*_test
	rm *.o
	rm -rf ./*.dSYM
