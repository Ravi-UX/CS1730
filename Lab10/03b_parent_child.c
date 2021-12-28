/******************************************************************************
* FILE: fork and wait
******************************************************************************/
#include <stdio.h>   // # prrintf
#include <unistd.h>  // # fork
#include <stdlib.h>  // # exit
#include <sys/wait.h>


pid_t childpid = -1;
int i;

int main( int argc, char *argv[] )
{
 int i = -55;

 if( (childpid = fork()) == 0 )
	{
	fflush(stdout);
	printf("[1. child  (%10d)]: i = %3d address = %p\n", childpid, i, (void*) &i );
	sleep(1);

	i = 11;

	printf("[2. child  (%10d)]: i = %3d address = %p\n", childpid, i, (void*) &i );

	//exit(0);
    	}
  else 
	{
	// try to make sure parent is executed after chid 'changes' i.
	sleep(10);
	printf("[b. parent (%10d)]: i = %3d address = %p\n", childpid, i, (void *) &i );
    	}

  //wait( (int *) 0 );

  printf("[w. parent (%10d)]: i = %3d address = %p\n", childpid, i, (void *) &i );
}
