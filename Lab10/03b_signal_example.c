#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <unistd.h> 

					// written to handle multiple signals //
static void sig_usr( int signo );	/* handles two signals */

static void sig_usr( int signo )
  {

  if( signo == SIGUSR1 )
	printf( "Received SIGUSR1\n" );
  else if( signo == SIGUSR2 )
	printf( "Received SIGUSR2\n" );
  else if( signo == SIGTERM )
	{
	printf( "Received SIGTERM\n" );	
    	signal(SIGTERM, SIG_DFL);
    	//raise(SIGTERM);
	}
  else
	{
	fprintf( stderr, "ERROR: received signal %d\n", signo );
	perror("bad signal number\n");
	exit(1);
	}
  return;
  }


int main( void )
  {
  int i = 0;
  if( signal( SIGUSR1, sig_usr ) == SIG_ERR )
	perror( "Cannot catch SIGUSR1\n" );
  if( signal( SIGUSR2, sig_usr ) == SIG_ERR )
	perror( "Cannot catch SIGUSR2\n" );

  if( signal( SIGTERM, sig_usr ) == SIG_ERR )
	perror( "Cannot catch SIGTERM\n" );

   while( 1 )
	{
	printf( "i= %d: ", i );
	printf( "%d %d: \n", SIGUSR1, SIGUSR2 );

	pause(); /* until signal handler
	           has processed signal */
	i++;
	}
   return 0;
  }

