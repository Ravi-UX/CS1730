CFLAGS = -g -Wall
CC = gcc

# if make followed by no target then will compile 'Hello'
all: mywc_commandline mywc part
# 3-generate-mystery-file

# before the "rm" there is only one white space character: a "TAB".
# If you have any  other white space this Makefile while not work

# before the "${CC}" there is only one white space character: a "TAB".
# If you have any  other white space this makefile while not work

mywc_commandline: mywc_commandline.c
	$(CC) $(CFLAGS) $@.c -o $@
mywc: mywc.c
	$(CC) $(CFLAGS) $@.c -o $@

3-generate-mystery-file: 3-generate-mystery-file.c
	$(CC) $(CFLAGS) $@.c -o $@

part: part.c
	$(CC) $(CFLAGS) $@.c -o $@

# generic
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f core *.o a.out mywc mywc_commandline 3-generate-mystery-file
	rm -f part
	rm -f XX-generate-mystery-file.bin
