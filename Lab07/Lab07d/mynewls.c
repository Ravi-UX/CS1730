#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include <time.h>

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

//returns the the width of the maximum file size in the directory
//takes num command line arguments and array storing command line args
int getMaxSize( int argc, char* argv[]) {
    char        *dirname = ".";
    struct dirent   *myfile = NULL;
    DIR         *mydir ;

    struct stat     mystat;
    int         err;
    struct passwd   *pwd;
    struct group    *grp;


    if( argc > 1 )
    dirname = argv[1];

    if( ! isdirectory( dirname ) )
    {
    printf("it is not a directory\n" );
    exit(1);
    }

     mydir = opendir( dirname );
     if( mydir == NULL )
     {
    perror("opendir");
    exit(1);
     }

     chdir(dirname);
     int max = 0;
     while( (myfile = readdir( mydir ) ) != NULL ) {
         int n = stat(myfile->d_name, &mystat);
         int size = mystat.st_size;
         if (size > max) {
             max = size;
         }
     }
     closedir(mydir);
     if (max < 10)
         return 1;
     if (max < 100)
         return 2;
     if (max < 1000)
         return 3;
     if (max < 10000)
         return 4;
     if (max < 100000)
         return 5;
     if (max < 1000000)
         return 6;

     return 0;
}

//Comparator function for two strings
int alphaComparator(const struct dirent **a, const struct dirent **b) {
    return strcasecmp( ( (*a)->d_name), (*b)->d_name);
}

//Returns the total used blocksize of the directory
// Takes number of command line args and array of command line args as parameters
int getBlkSize(int argc, char * argv[]) {
     char        *dirname = ".";
    struct dirent   *myfile = NULL;
    DIR         *mydir ;

    struct stat     mystat;
    int         err;
    struct passwd   *pwd;
    struct group    *grp;


    if( argc > 1 )
    dirname = argv[1];

    if( ! isdirectory( dirname ) )
    {
    printf("it is not a directory\n" );
    exit(1);
    }

     mydir = opendir( dirname );
     if( mydir == NULL )
     {
    perror("opendir");
    exit(1);
     }

     chdir(dirname);
     int blkSize = 0;
     while( (myfile = readdir( mydir ) ) != NULL ) {
         int n = stat(myfile->d_name, &mystat);
         blkSize += mystat.st_blocks;
         //printf("curr: %d\n", blkSize);
     }
     closedir(mydir);
     return blkSize/2;

}

int main( int argc, char* argv[] )
{
    int format = getMaxSize(argc, argv);
    int totalBlkSize = getBlkSize(argc, argv);
    char 		*dirname = ".";
    struct dirent **fNames;
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
     //chdir(dirname);
     printf("total %d\n", totalBlkSize);
    // subsequent calls of readdir returns the next entry in directory
    // as a struct dirent  (myfile), so the below traverses
    // the directory node, fully
     int i;
     int size = scandir(".", &fNames, 0, alphaComparator);
     //while( (myfile = readdir( mydir ) ) != NULL )
     for (i = 0; i < size; i++)
     {
        myfile = fNames[i];

	// place holder, prints out file/pathname
	 //  finish the rest so it
	// lools like ls -l as much as time permits.
	//

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
        int n = stat(myfile->d_name, &mystat);
    //char fType = mystat.st_mode;
    //char * perms = lsperms(n);
	// now you can print of further query what stat returns in
	// the reference parameter
	// 3) permissions
    printf("%s. ", lsperms(mystat.st_mode));
	// 4) links
    printf("%ld ", mystat.st_nlink);

	// 5)
	// to get the user name from st_uid in the stat
	// structure you can use
	// getpwuid()
	struct passwd *pwd = getpwuid( mystat.st_uid ); // assuming no error
    printf("%8.8s ",		pwd->pw_name);

	// 6)
        // group id is similar and you can get
        // to the string via getgrgid()
        //
    struct group *grp = getgrgid(mystat.st_gid);
    printf("%s ", grp->gr_name);
        // 7) size of file
        //
    int size = mystat.st_size;
    printf("%*d ", format, size);

    //time_t t = mystat.st_st_mtim.tv_sec;
    struct tm *timeInfo = localtime(&(mystat.st_mtim.tv_sec));
    char str[50];
    strftime(str, 50, "%b %e %H:%M", timeInfo);
    printf("%s ", str);

        // 8) name of file is last - already printed above
    printf("%s\n", myfile->d_name);



    }
    closedir(mydir);
    return 0;
}
