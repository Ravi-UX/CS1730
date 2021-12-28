CFLAGS = -g -Wall
CC = g++

all: 	FP_A		\
	FP_B		\
	FP_Euler2	\
	FP_Euler5	\
	FP_Euler6

FP_A: FP_A.c
	$(CC) $(CFLAGS) FP_A.c -o FP_A

FP_B: FP_B.cpp
	$(CC) $(CFLAGS) FP_B.cpp -o FP_B

FP_Euler2: FP_Euler2.cpp
	$(CC) $(CFLAGS) FP_Euler2.cpp -o FP_Euler2

FP_Euler5: FP_Euler5.cpp
	$(CC) $(CFLAGS) FP_Euler5.cpp -o FP_Euler5

FP_Euler6: FP_Euler6.cpp
	$(CC) $(CFLAGS) FP_Euler6.cpp -o FP_Euler6

clean:
	rm -f FP_A
	rm -f FP_B
	rm -f FP_Euler2
	rm -f FP_Euler5
	rm -f FP_Euler6
