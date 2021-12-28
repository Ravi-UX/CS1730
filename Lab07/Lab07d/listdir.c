#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>

int main( void )
	{
	DIR *dp;
	struct dirent *dir;

	if( (dp = opendir( "." )) == NULL )
		{
		fprintf( stderr, "Cannot open dir\n" );
		exit( 1 );
		}
	/* read entries */
	while( (dir = readdir( dp )) != NULL )
	{
		if( dir-> d_ino != 0 ) /* ignore empty records */
		{
			printf( "%s\n", dir->d_name );
			printf( "%d\n", (char) dir->d_type );
		}
	}
	closedir( dp );
	return 0;
	} /* end main */


