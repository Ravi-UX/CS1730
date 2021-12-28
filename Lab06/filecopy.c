/* ============================================================================
 Name        : mh_file_copy.c
 Author      : Maria Hybinette
 Description : Copy input file into output file
============================================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>			//  strdup()

#define D_BUFSIZE 	1		/* size of buffer for input and output */
					/* should be a block size, 512, 4096, 8192 */

#define NUM_ARGS 	4		/* required number of command line arguments */

#define ERROR_ARGS    	1
#define ERROR_OPEN_R  	2
#define ERROR_OPEN_W  	3
#define ERROR_WRITE   	4
#define ERROR_CALLOC    5

#define SUCCESS     	0
#define ERROR 	   	-1


int BUFSIZE = D_BUFSIZE;


int main( int argc, char * argv[] )
{
	int 	input_fd, output_fd;		/* file descriptors for i/o */
	ssize_t return_num_bytes_write,		/* number of bytes returned from write() */
        	return_num_bytes_read;		/* number of bytes returned from read()  */
	char    *buffer;         		/* character buffer -not allocated */
	char	*fn = strdup("filecopy");




	/* Q1a: NUM_ARGS is set in the #define  -- see above */
	// Change this argument so that it either accepts 3 or 4 arguments, if 4 it will
  	// if will use the command line block if 3 it should use a block size of 4,096.
    	// -----
     	printf("%s: Number of Arguments are: %d\n", fn, argc ); // comment this out later
    	// -----
	//
	if( argc != NUM_ARGS && argc != 3)
	{
		/* error message depends on linux implementation */
		printf( "%s: usage: cp source_file target_file BUFSIZE\n", fn );
		return ERROR_ARGS; /* #define on top of this program */
	}


	/* Q1: get BUFSIZE from command line - the last argument BUFSIZE */
		// filecopy <source_file> <target_file> <BUFSIZE>
		//
		// HINT convert argument from a string o an integer, use the c library routine:
		//   atoi( a_string )
		// modify the statement below
    if(argc == NUM_ARGS) {
        BUFSIZE = atoi(argv[3]); //Q1:replace D_BUFSIZE  with the commandline argument as an integer
    }

	/* allocates memory  a character buffer */
	/* calloc initializes the buffer to all 0s */
	buffer = ( char * ) calloc( BUFSIZE, sizeof(char));
	if( buffer == NULL )
	{
		/* perror prints a system error message along the argument */
		perror( "calloc" ) ;
		return ERROR_CALLOC ;
	}

	/* HINT 2 (can useful for Q2: allocate space for a constant
	 * string you can use strdup().
	 * Example USAGE:
	 *   #include <string.h>
	 *   char * temp;
	 *   temp = strdup( "PoP" );
	 *   allocates approprate space to store POP into the char
	 *   buffer temp
	 */


	/* Create user level read file descriptors */
	/* use the first argument on input line as the name the file */
	/* open it in Read Only - Mode - O_RDONLY */
 	/* more info on open : http://man7.org/linux/man-pages/man2/open.2.html */
	/* or  http://linux.die.net/man/2/open = not sure abou die.net but it   */
	/* loads really quicly! */
	/* when successful - open returns the lowest numbered file descriptor */
	/* not currently open for the process (this running program). */
	input_fd = open( argv[1], O_RDONLY );
	if( input_fd ==  ERROR )
	{
		/* perror prints a system error message along the argument */
		perror( "open" ) ;
		return ERROR_OPEN_R;
	}


	/* Create user level write file descriptors */
	/* write only, create it if it doen't excist, and RW owner, read others */
	output_fd = open( argv[2], O_WRONLY | O_CREAT, 0644 );
	if( output_fd ==  ERROR )
	{
		perror( "open" ) ;
		return ERROR_OPEN_W;
	}

	while(
	       /* read returns characters read, then this value is checked to
	        *  see if it is greater than 0, if not breaks out of the loop  */
	       (return_num_bytes_read = read( input_fd, buffer, BUFSIZE )) > 0
	     ) /* while parenthesis */
	{
		return_num_bytes_write =
			write ( output_fd, buffer, (ssize_t) return_num_bytes_read );
		if( return_num_bytes_read != return_num_bytes_write )
		{
			  perror("write");
	                  return ERROR_WRITE;
		}
	}

	/* Close file descriptors */
	close( input_fd );
	close( output_fd );

	return SUCCESS;
}
