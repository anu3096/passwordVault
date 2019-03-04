CC = gcc

all:
	$(CC) src/*.c -Iinclude -lncurses -Wall -std=c99 -o bin/runMe