//
// A simple but fairly efficient C version of the Unix "wc" tool
// modified from:
// http://www.opensource.apple.com/source/flex/flex-9/flex/MISC/fastwc/mywc.c
//
// #include <fcntl.h>
// #include <sys/types.h>

#include <stdlib.h>  	// for exit(), only
#include <unistd.h> 	// for STDIN_FILENO definition and read()
#include <ctype.h>  	// for isgraph()
#include <stdio.h>	// for printf()
#include <fcntl.h>

// ---------------------------------------------------------
//
// mygetC()
//
//
// Better to use c library getc - but we have not covered
// FILE * streams yet in details even if we used it for P1
// we also need to go lower level so we are doing that here.
//
//
// We are using POSIX read() - the glibc version of read()
// which  is a wrapper around Linux read()
// ---------------------------------------------------------
// returns character read, or EOF if the file pointer
// is beyond the end of the file
// exits on error
// ---------------------------------------------------------
int my_getC( int input_fd )
{
	char 	buffer[1] ={'\0'};
	int 	return_num_bytes_read;

	return_num_bytes_read = read( input_fd, buffer, 1 ) ;
	if ( return_num_bytes_read == 0 )
	{
		return EOF;
	}
	else if( return_num_bytes_read < 0 )
	{
		perror( "mygetC: " );
		exit(-1);
	}
	else
	{
		return (int) buffer[0];
	}
}


// ---------------------------------------------------------
// main()
// ---------------------------------------------------------
int main( int argc, char * argv[] )
{

	// register int's is a hint to keep these integers
	// in registers for quick access.
	//
	// It not guaranteed that these requests to be
	// in registers are granted.
	//
	register int c, cc = 0, wc = 0, lc = 0;

	int input_fd = STDIN_FILENO;

	// the input may be a file open file perhaps here?
    if (argc >= 2) {
        input_fd = open(argv[1], O_RDONLY);
    }

	while ( (c = my_getC( input_fd )) != EOF )
	{
		++cc;
		if( isgraph(c) )
				// Checks for any printable character
				// except space (isgraph()). //ctype.h
				//
				// Check if the first part is a readable
				// word, will parse until the end of
				// the word
		{
			++wc;	// wc - word count is incremented
			do
			{
				// go until seeing  a non printable
				// character (e.g., white space), unless it is EOF
				// then we would like to get out of there.
				c = my_getC( input_fd );

				if( c == EOF ) // check for EOF
				{ // goto statements are controversial.
				 //  it goes to label "done:" further below
					goto done;
				}

				++cc; // character count is incrementd

			} while ( isgraph(c) );
		}

		// not isgraph so check for a new line
		if (c == '\n')
			++lc; // increment line count.
	}

done:
	printf( "%8d%8d%8d\n", lc, wc, cc );
}
