CFLAGS = -g -Wall -Wno-unused-variable
OBJECTS = permissionbits.o

CC = gcc

all: myls mynewls

mynewls: mynewls.o $(OBJECTS)
	$(CC) $(CFLAGS) $@.o $(OBJECTS) -o $@  

myls: myls.o $(OBJECTS)
	$(CC) $(CFLAGS) $@.o $(OBJECTS) -o $@  


# generic
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f mynewls
	rm -f myls
	rm -f core *.o a.out 
	rm -f DIRECTORY.html
	rm -rf *.dSYM

webclean:
	rm -f DIRECTORY.html

