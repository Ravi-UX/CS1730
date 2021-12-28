

#include <limits.h>
double running_average( int add_number )
{
	static double total_numbers 	= 0;
	static double total_sum 	= 0;

	total_sum = total_sum + (double) add_number ;
	total_numbers += 1;

	return total_sum / total_numbers;
}

double sum( int add_num )
{
	static double total_sum = 0;

	total_sum += add_num;

	return total_sum;
}

double sum_squares( int add_num )
{
	static double total_sum = 0;

	total_sum += add_num * add_num;

	return total_sum;
}

double sample_var( int add_num )
{
	static double total_numbers = 0;
	static double total_sum = 0;
	static double variance = 0;
    static double sum_squ = 0;

	total_sum += (double) add_num;
	total_numbers += 1;
    sum_squ += add_num * add_num;

	double mean = total_sum / total_numbers;
    variance = ((sum_squ) - (2 * mean * total_sum) + (total_numbers * mean * mean)) / total_numbers;
	return variance;

}
int min( int num )
{
	static int minimum = INT_MAX;
	if (num < minimum) {
		minimum = num;
	}
	return minimum;
}

int max( int num )
{
	static int maximum = INT_MIN;
	if (num > maximum) {
		maximum = num;
	}
	return maximum;
}
