CFLAGS = -g -Wall
CC = g++

all: twisted

twisted: twisted.cpp twistedf.cpp twistedf.h
	$(CC) $(CFLAGS) twisted.cpp twistedf.cpp -o twisted

clean:
	rm -f twisted
