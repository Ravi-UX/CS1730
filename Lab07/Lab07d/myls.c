#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include <pwd.h>
#include <grp.h>

#include "permissionbits.h"



// 
// isdirectory()  --  checks wheter the file: filename is a directory or not. 
//  	returns 1 if it is a directory,
//   	returns 0. not directory or doesn't exit.
//  illustrates usage of stat
int isdirectory( char * filename )
{
int 			err;
struct  stat        	mystat;

	err = stat( filename, &mystat );
 	if( -1 == err ) 
	{
    		if( ENOENT == errno )
		{
        		/* does not exist */
			return 0;
    		} 
		else 
		{
        		perror( "stat" );
        		exit(1);
    		}
	} 
	else  // no error 
	{
    		if( S_ISDIR( mystat.st_mode) ) 
		{
        	/* it's a dir */
		return 1;
    		} 
		else 
		{
        	/* exists but is not a directory */
		printf("ls: %s: No such file or directory", filename );
		return 0;
    		}
	}

}


int main( int argc, char* argv[] )
{
    char 		*dirname = ".";
    struct dirent 	*myfile = NULL;
    DIR 		*mydir ;

    struct stat 	mystat;
    int 		err;
    struct passwd 	*pwd;
    struct group 	*grp;


    if( argc > 1 )
	dirname = argv[1];

    if( ! isdirectory( dirname ) )
	{
	printf("it is not a directory\n" );
	return 1;
	}

     mydir = opendir( dirname );
     if( mydir == NULL )
     {
	perror("opendir");
	return 1;
     }


    // in while loop below
    // 	stat() reads from the current directory 
    // consider using chdir().
    // man chdir to check how to use chdir();
       // 1) --> below add 'chdir() line below:


    // subsequent calls of readdir returns the next entry in directory 
    // as a struct dirent  (myfile), so the below traverses
    // the directory node, fully
    while( (myfile = readdir( mydir ) ) != NULL )
    {

	// place holder, prints out file/pathname 
	 //  finish the rest so it
	// lools like ls -l as much as time permits.
	// 
	printf("%s\n", myfile->d_name); 

	// call stat() on file name  to get info on the file
	// the name of the file in the 
	 // struct dirent myfile 
	// you need to make sure that you return a reference to
	// the struc mystat, i.e., &mystat ('&' denotes a reference).
	//
   	// int stat(const char *pathname, struct stat *mystat);
	//
	// man 2 stat
	//
	// 2) ---> below add call to stat() check for error
 	//
	// from mystat you can get all sorts of info
	// mystat.st_mode for PERMISSIONS, and you
	// can convert the string using the provided lperms() function, 
	// see permissionbits.c that provides this function

	// now you can print of further query what stat returns in 
	// the reference parameter
	// 3) permissions
	// 4) links


	// 5) 
	// to get the user name from st_uid in the stat
	// structure you can use 
	// getpwuid()
	// pwd = getpwuid( mystat.st_uid ); // assuming no error
        // printf("%8.8s",		pwd->pw_name);
        
	// 6)
        // group id is similar and you can get
        // to the string via getgrgid()
        //
        // 7) size of file
        //
        // 8) name of file is last - already printed above
          

    }
    closedir(mydir);
    return 0;
}
