FEP
-----------------------------------------------------------------------------------------------
This directory contains a series of programs which are solutions to some interview questions
and Euler like problems.
-----------------------------------------------------------------------------------------------

CODER: Ravi Cheekati
CREDIT/CONTRIBUTIONS:


Compile command for all programs in directory using provided Makefile:
        make clean
        make

Description and Run commands for each program:
    ./FP_A [nums.txt]
    This program takes in some text file nums.txt containing integers as a command line argument
    and stores the integers in an array. Then the contents are sorted such that all of the
    0s are moved to the right side of the array. The final array is printed to stdout.

    ./FP_B [nums.txt]
    This program takes in some text file nums.txt containing integers as a commandline argument
    and sotres the integers in an array. Then the program attempts to find an element in the array
    such that the element is the same as the index of the element.

    ./FP_Euler2
    This program finds the sum of all the even valued terms of the Fibonacci
    sequence that do not exceed 4,000,000.

    ./FP_Euler5
    This program finds the smallest positive number that is evenly divisible
    by all of the numbers from 1-20.

    ./FP_Euler6
    This program finds the difference between the sum of the squares of the
    first 100 natural numbers and the square of the sum.

(Commands must be executed within the project directory)
