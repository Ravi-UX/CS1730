#include <stdio.h>
#include <stdlib.h>


void print_array( int * array, int size )
{
   	for( int i= 0; i < size ; i++ )
		printf("array[%2d] = %d\n", i, array[i] );
	printf("\n");
}

//int main( int argc, char* argv[] )
int main( )
{
  char x[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
  //int  numbers[] = { 5, 4, 3, 2, 1 };
  //long Lnumbers[] = { 1001, 1002, 1005};

  char  * char_ptr;
  short * short_ptr;
  int   * int_ptr;
  long  * long_ptr;

  char y[] = { 'a', 'b', 'c', '\0', 'e', 'f', 'g', 'h', 'i', 'j', '\0' };
  printf("y is: %s\n", y);
  int_ptr = (int *) y;
  int_ptr += 1;
  printf("int_ptr: %s\n", (char *) int_ptr );

  printf("x is: %s\n", x);

  printf("sizeof(char)  = %lu\n", sizeof(char));
  printf("sizeof(short) = %lu\n", sizeof(short));
  printf("sizeof(int)   = %lu\n", sizeof(int));
  printf("sizeof(long)  = %lu\n", sizeof(long));

  char_ptr = x;
  char_ptr += 1;
  printf("incremented by char:  %c\n", (int) char_ptr[0]);

  short_ptr = (short *) x;
  short_ptr += 1;
  printf("incremented by short: %c\n", (int) short_ptr[0]);

  int_ptr = (int *) x;
  int_ptr += 1;
  printf("incremented by int:   %c\n", (int) int_ptr[0]);

  long_ptr = (long *) x;
  long_ptr += 1;
  printf("incremented by long:  %c\n", (int) long_ptr[0]);

  char *pointlessptr = "howmuchlonger";
  printf( "%c\n", *&*&*pointlessptr );                   // a)
  printf( "%lx\n", (long) *&*&*pointlessptr );        //  b)
  printf( "%lx\n", (long) &*&*pointlessptr );         //  c)

  return 0;
}
