# CFLAGS=-Wall -g
CFLAGS=-Wall -g -fsanitize=address -fno-omit-frame-pointer

all: vector_test

vector.o: vector.c

vector_test: vector_test.c vector.o

clean:
	rm ./vector_test
	rm *.o
	rm -rf ./*.dSYM
