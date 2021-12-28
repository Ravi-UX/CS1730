#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#include <stdlib.h>

#define BUFFYSIZE 1

int main( void )
  {
  int fd, count;
  char buffer[BUFFYSIZE];

  //
  // Writes to the current's process 'terminal session' (tty)
  // you can print yoru login terminal session by simply
  // typing tty on your bash command line.
  //
  // To make this communication work better,  you are going 
  // change tty (current session) to
  // use a file from the /tmp directory
  //
  // This file, or really 'port',  should be created using the
  // unix command mkfifo, and removed in you
  // makefile via the make clean command
  //
  // mkfifo /tmp/<your_name_all_lower_case>_<unique-4_DIGITnumber>
  //
  //  Example: name = alice, unique-4 digit=1234
  //
  // Example:
  //  mkfifo /tmp/alice_1234
  //  
  // In Makefile, edit the make clean command   
  // and remove your tmp file, in the clean command
  //  
  //   -- replace /dev/tty below 
  //
  if( (fd = open( "/dev/tty", O_RDWR )) < 0 )
 	{
   	fprintf( stderr, "Cannot open port\n" );
	exit(55);
   	}
  
  if( fork() > 0 )
  {    /* parent */
  	while( 1 )
     	{
		// reads from tty or file/port in tmp directory
     		count = read( fd, buffer, BUFFYSIZE );

		// writes to stdout
     		write( 1, buffer, count );
     	}
  }
  else 
  {                /* child */
  	while( 1 )
     	{
		// reads from stdin 
     		count = read( 0, buffer, BUFFYSIZE );

		//  writes to tty or file/port in tmp directory
     		write( fd, buffer, count );
     	}
  }       /* else */

  return 0;

} /* main */

