#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h> 

int beeps = 0;

static void handler( int signo )
  {
  printf( "BEEP\n" );
  fflush(stdout);

  if( ++beeps < 5 )
        alarm(1);
  else
        {
        printf("BOOM!\n");
        exit(0);
        }
  return;
  }


int main( void )
  {
  int i = 0;
  if( signal( SIGALRM, handler ) == SIG_ERR )
        perror( "Cannot catch SIGALRM\n" );
  alarm(1);
  while( 1 )
        {
        printf( "%d: ", i );
        pause(); i++;
        }
   return 0;
  }





