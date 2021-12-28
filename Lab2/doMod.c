
/*
	https://www.geeksforgeeks.org/modulo-operator-in-c-cpp-with-examples/

	// Program to illustrate the
	// working of the modulo operator
*/
 
#include <stdio.h>
 
int main(void)
{
 
    // To store two integer values
    int x, y;
 
    // To store the result of
    // the modulo expression
    int result;
 
    x = 9;
    y = 4;
    result = x % y;
    printf("%d %% %d = %d\n", x, y, result);
 
    x = 7;
    y = 2;
    result = x % y;
    printf("%d %% %d = %d\n", x, y, result);
 
    x = 3;
    y = 4;
    result = x % y;
    printf("%d %% %d = %d\n", x, y, result);

    
    x = 5;
    if( x % 2 == 0 )
    {
    	printf("x = %d is even\n", x );
    }
    else
    {
    	printf("x = %d is odd\n", x );
    }


    x = 8;
    if( x % 2 == 0 )
    {
    	printf("x = %d is even\n", x );
    }
    else
    {
    	printf("x = %d is odd\n", x );
    }
 
    return 0;
}
