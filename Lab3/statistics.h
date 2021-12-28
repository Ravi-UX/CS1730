// only include declaration once, by defining prepprocessor 'dummy variable'
#ifndef STATISTICS_H   
#define STATISTICS_H


extern double running_average( int add_number );
extern double sum( int add_num );
extern double sum_squares( int add_num );
extern double sample_var( int add_num );
extern int min( int num );
extern int max( int num );



#endif

