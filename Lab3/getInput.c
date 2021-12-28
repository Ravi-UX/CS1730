#include <stdio.h>


#define MAX_LINE 80

// functions from statistics.c, prototype is in statistic.h
#include "statistics.h"


/* ---
 *  getIntegerLine()
 * 	returns a positive integer from a line of input
 *
 *      Assumption: assumes proper input.
*/
int getIntegerLine()
{
        char    line[MAX_LINE];
        int     return_user_int=-1;

        fgets( line, sizeof( line ), stdin );
        while( sscanf( line, "%d", &return_user_int ) != 1 )
        {
                // Not a positive integer - indicates end of input
		return -1;
        }
        return return_user_int;
}


/* ---
 *      prompts user for input.
*/
void promptList()
{
	printf( "\nAssumes proper input \n\n" );
    printf( " Type a list of non-negative integers, below, one integer per line\n" );
    printf( " Indicate the END of input with any letter (a-z):\n\n"  );
}



void driver()
{
	int anumber=-1;

	//promptList();
	static double sums = 0;
	static double avg = 0;
	static double sum_sq = 0;
	static double sam_var = 0;
	static int minimum = 0;
	static int maximum = 0;

	while( (anumber = getIntegerLine()) >= 0 )
	{

		sums = sum( anumber );
		avg = running_average( anumber );
		sum_sq = sum_squares( anumber );
		sam_var = sample_var( anumber );
		minimum = min( anumber );
		maximum = max( anumber );
	}

	printf( "            Sum: %4.2lf\n", sums);
    printf( "        Average: %4.2lf\n", avg);
    printf( " Sum of Squares: %4.2lf\n", sum_sq);
    printf( "Sample Variance: %4.2lf\n", sam_var);
    printf( "        Minimum: %d\n", minimum);
    printf( "        Maximum: %d\n", maximum);

}
