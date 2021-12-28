#include <stdarg.h>
#include <stdio.h>

// compute the average of an arbitrary number of arguments.
// https://en.wikipedia.org/wiki/Variadic_function#In_C
double average( int count, ... )
{
    va_list ap;
    int j;
    double sum = 0;

    // placeholder at the last argument before ellipses
    va_start( ap, count ); /* Requires the last fixed parameter (to get the address) */
	
    for( j = 0; j < count; j++ )
    {
	// type of arguments of the ellipses
        sum += va_arg( ap, int ); /* Increments ap to the next argument. */
    }
   // marks the end
    va_end( ap );

    return sum / count;
}

int main() 
{
    printf("%4.2f\n", average( 5, 1, 2, 3, 8, 9 ) );
    printf("%4.2f\n", average( 3, 1, 2, 3  ) );
    return 0;
}
