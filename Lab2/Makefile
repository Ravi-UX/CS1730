#CFLAGS= -lreadline 
DEBUG=-g -Wall
# DEBUG=

all: doMod game_1

doMod: 	doMod.c
	gcc  $(CFLAGS) $(DEBUG) doMod.c -o doMod

game_1:	game_1.c
	gcc $(CFLAGS) $(DEBUG) game_1.c -o game_1

clean:
	rm -f doMod game_1 

