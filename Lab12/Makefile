# compiles the program in File: "Hello.cpp", by typing "make" on
# the command line
CFLAGS = -g
CC = g++

# if make followed by no target then will compile 'Hello'
all: doTime \
	pred \
	lab12

# before the "rm" there is only one white space character: a "TAB".
# If you have any  other white space this Makefile while not work
clean:
	rm -f core *.o a.out doTime pred

# before the "${CC}" there is only one white space character: a "TAB". 
# If you have any  other white space this makefile while not work
#
# your project add line for target lab12:
doTime: doTime.o
	$(CC) $(CFLAGS) -o $@ $@.o 

lab12: lab12.o
	$(CC) $(CFLAGS) -o $@ $@.o

# example cout << operator 
pred: pred.o
	$(CC) $(CFLAGS) -o $@ $@.o 

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
