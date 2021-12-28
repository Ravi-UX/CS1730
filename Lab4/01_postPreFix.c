#include <stdio.h>


//
// Order precedence & ptr arithmetic
//
// 1) Create a copy of the variable
// 2) Increments the variable (not the copy)
// 3) Postfix x++ returns the copy of the unincremented (original) variable
//
// 1) Increment the variable
// 2) Prefix ++x returns the reference of the incremented variable,
//
// operator priority:
// () parenthesized expressions superseded the below.
// ++ is higher priority than (we increment 'content' first)
// *  dereferencing priority (then we dereference)
//
// https://en.cppreference.com/w/cpp/language/operator_incdec
//


int main()
{
  int myarray[] = { 100, 200, 300, 400, 0 };
  int out = 0;
  int *my_ptr = myarray;


  // post fix add.
  // ++ has higher priority than *

  int i = 0;
  while( (out = *++my_ptr) != 0)
  {
    if(*my_ptr == myarray[1])
    {
        out = *--my_ptr;
        printf("%d ", out);
        out = *++my_ptr;
    }
  	printf("%d ", out);
  }
  printf( "d) while( (out = *my_ptr++) != 0 ) {} " );  // ==> A.
  printf( "\n" );
  printf( "out = %d", out );
  printf( "\n" );


  // create a similar while loop creating the same
  // output BUT that increment the pointer prefix.
  // of ++ that prints out the array -
  // i.e, you just have  ++my_ptr within the while expression
  //

return 0;
}
