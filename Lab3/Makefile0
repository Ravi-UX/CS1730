CFLAGS  = -g -Wall
CC	= gcc

all: runProgram longProgram

# checks time stamps on all pre-requisites and check if it needs
# recompilation
runProgram: runProgram.c statistics.c getInput.c statistics.h
	$(CC) $(CFLAGS) statistics.c getInput.c runProgram.c -o runProgram




longProgram: longProgram.c 
	$(CC) $(CFLAGS) $@.c -o $@

clean:
	rm -f runProgram
	rm -f longProgram
	rm -f *.o
	rm -rf runProgram.dSYM
	rm -rf longProgram.dSYM

