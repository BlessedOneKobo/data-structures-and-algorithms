# CFLAGS=-Wall -g
CFLAGS=-Wall -g -fsanitize=address -fno-omit-frame-pointer

clean:
	rm -rf ./*.dSYM
