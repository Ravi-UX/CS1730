/* ============================================================================
 Name        : English to Goggamal translator
 Author      : Maria Hybinette
============================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h> 	// for isalpha() 
#include <string.h> 	// for strdup() is in here

#define BUFFYSIZE   1

char    *temp;
char    *write_buf;


int aconsonantSWITCH( char ch )
{
	int aConsonant = 1;
	int notConsonant = 0;

        if( isalpha(ch) == 0 )
        {
                return notConsonant;
        }

	aConsonant = 0;
	if( ch =='a'||ch=='A'||ch=='e'||ch=='E'||ch=='i'||ch=='I'||ch=='o'||ch=='O'||ch=='u'||ch=='U')
	{
		aConsonant = 0;
	}
	else
	{
		aConsonant = 1;
	}
	return aConsonant;
}


int main( int argc, char * argv[] )
{
	int 	input_fd, output_fd;		/* file descriptors for i/o */
	ssize_t return_num_bytes_write,		/* number of bytes returned from write() */ 
        	return_num_bytes_read;		/* number of bytes returned from read()  */
	char    buffer[1] = {0};       		/* character buffer -not allocated */

	temp = strdup( "PoP" );			 /* fake buffer w/ o in the middle */

	/* use regular stdin and stdout for reading and writing */
	input_fd  = STDIN_FILENO;
	output_fd = STDOUT_FILENO;


	while( (return_num_bytes_read = read( input_fd, buffer, BUFFYSIZE ) ) > 0 ) /* while parenthesis */
	{
		char ch = buffer[0];

		write_buf = buffer;
		if( aconsonantSWITCH( ch ) )
		{
			temp[0] = ch;
			temp[2] = ch;
			return_num_bytes_read = 3; // HACK! 
			write_buf = temp;
		}

		return_num_bytes_write = write ( output_fd, write_buf, (ssize_t) return_num_bytes_read );
		if( return_num_bytes_read != return_num_bytes_write )
		{
			perror("write");
	               	return 4;
		}
	}
	return 0;
}
