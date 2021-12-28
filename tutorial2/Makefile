CC = gcc
CFLAGS = -g -Wall 
# -Wextra -Werror 

all: casting datatypes pointers-basicA  pointers-basicB pointers promote thestruct0 thestruct1

% :  %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $@.c -o $@

queue: main.c student-queue.c
	$(CC) $(CFLAGS) -o student_queue_test student-queue.c main.c

ref-queue: main.c ref-queue.c
	$(CC) $(CFLAGS) -o ref_queue_test ref-queue.c main.c

clean:
	rm -f casting datatypes pointers-basicA  pointers-basicB pointers promote thestruct0 thestruct1 *.o
