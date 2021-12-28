#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
  	{
	if( open( "temp", O_RDWR ) < 0 )
		{
		perror( "open error" );
		exit( 1 );
		}
	if( unlink( "temp" ) < 0 )
		{
		perror( "unlink error " );
		exit( 1 );
		}
	printf( "file temp is unlinked\n" );
	exit( 0 );
  	}

