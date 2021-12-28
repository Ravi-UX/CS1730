#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>

#include	<sys/types.h>
#include 	<sys/stat.h>

// ------------------------
// run with :
// 	part 20 > part.bin
// ------------------------

char	buf1[] 		= "funixISawesome"; /* 14 letters [a-zA-Z] */
char	buf2[] 		= "FUNIXisAWESOME"; /* 14 letters [a-zA-Z] */
char	buf3[2]		= {'\b', '\b'};
char	buf4[23] 	= "funix is awesome\b\a\a\a\a";


int main(int argc, char *argv[])
{
	int		fd = STDOUT_FILENO;

	if( argc < 2 )
	{
		printf( "part: Must specify size\n");
		printf( "usage: part size_bytes >  file_name\n" );
		printf( "example:\npart 20 > part.bin\n" );
		exit(1);
	}
	int 		myoffset = atoi( argv[1] );

	// add buf1 to new file
	if( write( fd, buf1, sizeof( buf1 ) ) != sizeof( buf1 ) )
		perror("buf1 write error");
		/* offset now = xx */

	// forward file pointer - fills in betweens with '\0'
	if( lseek( fd, myoffset, SEEK_CUR ) == -1 )
		perror("lseek error");
		/* offset now = ?  */

	if( write( fd, buf2, sizeof(buf2) ) != sizeof(buf2) )
		perror("buf2 write error");
		/* offset now = ? */

	if( write( fd, buf3, sizeof(buf3) ) != sizeof(buf3) )
		perror("buf3 write error");
		/* offset now = ? */

	if( write( fd, buf4, sizeof(buf4) ) != sizeof(buf4) )
		perror("buf4 write error");
		/* offset now = ? */
	exit(0);
}
