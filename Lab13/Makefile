CFLAGS = -g -Wall
CC = g++
LDFLAGS =

BIN =   get_input \
	map_bikes \
	map_nested \
	multimap_words \
	Lab13
# if make followed by no target then will compile 'Hello'
all: $(BIN) 

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@ 

$(BIN): %: %.o
	$(CC) $(CFLAGS) $@.o -o $@  $(LDFLAGS)

clean :
	-rm -f a.out *.o core atest
	-rm -f *.class
	-rm -f  $(BIN) 
