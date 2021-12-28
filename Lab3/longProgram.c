#include <stdio.h>
#include <unistd.h> // sleep
#include <stdlib.h> // atoi

int main( int argc, char *argv[] )
 {
 int a,i;
 int inseconds=300; // 300 seconds = 5 minutes

 a=5;
 if( argc > 1 )
	{
	//printf("%s\n", argv[1]);
	inseconds = atoi(argv[1]);
	}

 for (i=0; i < inseconds; i++) 
	{ 
	a = a+i; 
	sleep(1);
	}

 printf("%d\n", a);
}

