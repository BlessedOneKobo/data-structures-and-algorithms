CFLAGS=-Wall -g
# CFLAGS=-Wall -g -fsanitize=address -fno-omit-frame-pointer

all: vector

clean:
	rm ./vector
	rm -rf ./*.dSYM
