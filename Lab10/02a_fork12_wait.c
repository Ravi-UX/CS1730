#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 4


void fork12() 
{ 

 pid_t pid[N];   	// large family
 int child_status; 
 int i; 

 for( i = 0; i < N; i++ ) 
 {
 	if( (pid[i] = fork()) == 0 )
	{
		while(1); 
	} /* Child infinite loop */ 
 }

 // man -2 wait

 /* Parent terminates the child processes */ 
 for( i = 0; i < N; i++ )
 { 	
	printf( "Killing process %d\n", pid[i]); 
	//kill( pid[i], SIGINT ); // INT interrupt signal  
	kill( pid[i], SIGTERM ); // TERM signal   kill -l to see ((15)
 } 
 /* Parent reaps terminated children */ 
 for (i = 0; i < N; i++) 
 {
	pid_t wpid = wait(&child_status); 

	if( WIFEXITED(child_status) ) 
	// This macro returns a nonzero value if the child process terminated 
  	// normally with exit or _exit.
	{
		printf("Child %d terminated normally with exit status %d\n",
			 wpid, WEXITSTATUS(child_status)); 
	}
	else 
	{
 		printf("Child %d terminated abnormally by a signal (%d) ", 
				wpid, WIFSIGNALED(child_status) ); 
		// WIFSIGNALED -- Returns true if killed by a signal
 		printf(" by signal# %d\n", WTERMSIG(child_status) ); 
		// WTERMSIG -- Returns true if killed by a signal
	}
 } /* for */
} /* fork12 */


int
main()
{
	fork12(); // create chilren - more than 1 
	return 0;
}
