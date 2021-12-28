CFLAGS  = -g -Wall
CC	= gcc


all: 01_postPreFix 03_0fpointers 03_A_activity 03_B_activity

#
# checks time stamps on all pre-requisites and check if it needs
#
# recompilation
# https://www.gnu.org/software/make/manual/html_node/Automatic-Variables.html
#

%: %.o 
	$(CC) $(CFLAGS) $^ -o $@

%.o : %.c 
	$(CC) $(CFLAGS) -c $<


clean:
	rm -f 01_postPreFix
	rm -f 03_0fpointers
	rm -f 03_A_activity
	rm -f 03_B_activity
	rm -f 
	rm -f *.o
	rm -rf *.dSYM

