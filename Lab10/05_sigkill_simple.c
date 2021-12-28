#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sig_handler ( int signum) 
{ 
	printf("Handled the signal\n");
}


int main() 
{
  int pid;

  signal( SIGKILL, sig_handler ); // install handler

  pid = fork();			  // fork

  if( pid==0 )
  {
        kill( getppid(), SIGKILL ); // send signal
        exit(0);
  }

  else
  {
        sleep(20);		//parent.
				
  }
				
  return 0;
}
