CC = gcc
CFLAGS = -g -Wall -Wextra 
#-Werror -std=gnu99

all:  arbitrArgs fpointers macros  mem_mgmt passing_args pointer_arithm  \
	typedefs typedefs2 typedefs3

macros:
	$(CC) -o macros macros.c 

%: %.c
	$(CC) $(CFLAGS) -o $@ $@.c 

clean:
	rm -rf arbitrArgs fpointers macros 
	rm -rf mem_mgmt passing_args pointer_arithm 
	rm -rf thestruct[0-9] typedefs typedefs
	rm -rf typedefs[0-9]
	rm -rf pointer_arithm[0-2]
	rm -rf mallocing
	rm -rf *.dSYM
