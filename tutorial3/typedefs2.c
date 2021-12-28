#include <stdio.h>

typedef int number;

typedef struct  TAG  {  int x; int y; }   point;

// don't need the tag for the struct;
//typedef struct      {  int x; int y; }   point;

int main(void)  
{ 
 /* Define a variable p of type point, and inialize all its members inline */  
	point p2;   
	point p1 = { 1, 2 };  
     
	p2  =  p1;  // p2.x = 1 and p2.y=2 
	p2.x = 2;   // unequalize

/* Demonstrate we have a copy and that they are now different. */  
     if( p1.x != p2.x )
     {
           printf( " p1.x != p2.x not equal! %d != %d\n", p1.x, p2.x );  
     }
     else
     {
           printf( "ERROR p1.x == p2.x are equal! %d != %d\n", p1.x, p2.x );
     }
	

return 0; } 
