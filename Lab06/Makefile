CFLAGS = -g
CC = gcc

# if make followed by no target then will compile 'Hello'
all: filecopy makegoggamal

# before the "rm" there is only one white space character: a "TAB".
# If you have any  other white space this Makefile while not work

# before the "${CC}" there is only one white space character: a "TAB".
# If you have any  other white space this makefile while not work

filecopy: filecopy.o
	$(CC) $(CFLAGS) $@.c -o $@
makegoggamal: makegoggamal.c
	$(CC) $(CFLAGS) makegoggamal.c -o makegoggamal

# generic
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f core *.o a.out
	rm -f filecopy
	rm -f goggamal
	rm -f goggamal-stdin-stdout
	rm -f DIRECTORY.html
	rm -f makegoggamal
	rm -rf *.dSYM

webclean:
	rm -f DIRECTORY.html
