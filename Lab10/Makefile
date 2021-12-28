CFLAGS = -g -Wall
CC = gcc

all: 	02a_fork12_wait   \
	03b_parent_child \
	03a_signal_example \
	03b_signal_example \
	04_signal_example \
	05_sigkill_simple \
	lab10


# generic
%: %.o
	$(CC) -g $@.c -o $@
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f core *.o a.out lab10
	rm -f 02a_fork12_wait
	rm -rf 03b_parent_child
	rm -f 03a_signal_example
	rm -f 03b_signal_example
	rm -f 04_signal_example
	rm -f 05_sigkill_simple
	rm -f lab10
