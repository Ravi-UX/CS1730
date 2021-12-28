CFLAGS = -g -Wall
CC = gcc

all: runProgram

runProgram: craps.c wagers.c wagers.h
	$(CC) $(CFLAGS) craps.c wagers.c -o runProgram

clean:
	rm -f runProgram
