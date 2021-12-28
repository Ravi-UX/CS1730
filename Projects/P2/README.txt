chunk.c
-----------------------------------------------------------------------------------
This program takes a text file as input and divides it by number of lines, words,
or characters based on the provided options.
--------------------------------------------------------------------------------------

CODER: Ravi Cheekati
CREDIT/CONTRIBUTIONS:
Lab 05
Lab 06
geeksforgeeks.com


Compile command:
        gcc -g -Wall chunk.c chunkFunctions.c -o chunk

Or use provided Makefile:
   make clean
   make

Run command:
    ./chunk [options] -f filename.txt [-p prefix] [-s suffix]
    ./chunk [options] [-p prefix] < filename.txt

(Commands must be executed within the project directory)
