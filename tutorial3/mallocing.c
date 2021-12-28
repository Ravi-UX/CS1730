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
  int numbers[] = { 5, 4, 3, 2, 1 };

  int * number_ptr;
  int * number_ptr0;

  // bytes in the array 
  size_t size = sizeof(numbers);

  // number of elements in `numbers`
  size_t length = sizeof(numbers) / sizeof(numbers[0]);

  // print results
  printf("numbers = %zu bytes, %zu elements\n", size, length );

  // print elements
  print_array( numbers, 5 );

  numbers[2] =  67;
  numbers[0] =  55;

  number_ptr = numbers;
  number_ptr[4] = 105;

  // change value that num_ptr
  print_array( numbers, 5 );

  number_ptr = (int *) malloc( 4 * sizeof(int) );

  *number_ptr = 99;
   number_ptr0 = number_ptr;
  print_array( number_ptr0, 4 );

  number_ptr += 1;
  *number_ptr = 98;
  print_array( number_ptr0, 4 );

  number_ptr += 1;
  *number_ptr = 97;
  print_array( number_ptr0, 4 );

  print_array( number_ptr, 4 ); // can be an error

  free(number_ptr0);

  return 0;
}

