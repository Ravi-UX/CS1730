#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

#include <string.h>


//
// Checks wheter the file: filename is a directory or not.
//      returns 1 if it is a directory,
//      returns 0 if not directory or doesn't exist.
//
int isdirectory( char * filename ) {
    int             err;
    struct  stat            mystat;

    err = stat( filename, &mystat );
    if( -1 == err ){
        if( ENOENT == errno ) {
                // does not exist
            printf("%s does not exist\n", filename);
            exit(1);
        }else{
            perror( "stat" );
            exit(1);
         }
    } else {
        //Check if directory
        if( S_ISDIR( mystat.st_mode) ) {
            // it's a dir
            return 1;
        } else {
            /* exists but is not a directory */
            return 0;
        }
    }

}

// Checks whether file: filename has read and/or execute permissions: perms
//     Returns 1 if has permissions
//     Returns 0 if it does not have permissions
int testPerms( char * filename, int perms) {
    //Test file permissions for read and execute access
    if ( perms == 5 && access(filename, R_OK | X_OK) != -1)
        return 1;
    //Test file permissions for read access
    if ( perms == 4 && access(filename, R_OK) != -1)
        return 1;

    return 0;
}

// Checks whether a file is of the same type as entered by the user.
// Also takes stat structure: mystat which must be populated with the file's
// data using lstat() before being passed a parameter
//     Returns 1 if matching type is found or if no type is entered
//     Returns 0 if no matching type is found
int checkType(struct stat mystat, char type) {
    if (type == '\0')
        return 1;
    //Check if file is block
    if (type == 'b' && (S_ISBLK(mystat.st_mode) != 0))
        return 1;
    //Check if file is character
    if (type == 'c' && (S_ISCHR(mystat.st_mode) != 0))
        return 1;
    //Check if file is directory
    if (type == 'd' && (S_ISDIR(mystat.st_mode) != 0))
        return 1;
    //Check if file is a pipe
    if (type == 'p' && (S_ISFIFO(mystat.st_mode) != 0))
        return 1;
    //Check if file is regular
    if (type == 'f' && (S_ISREG(mystat.st_mode) != 0))
        return 1;
    //Check if file is symlink
    if (type == 'l' && (S_ISLNK(mystat.st_mode) != 0 ))
        return 1;
    //CHeck if file is a socket
    if (type == 's' && (S_ISSOCK(mystat.st_mode) != 0))
        return 1;

    return 0;
}

//Searches a directory: dirname for a matching substring: str and type: t
//Returns void
void searchdir( char * dirname, char * str, char type) {
    struct dirent * myfile = NULL;
    struct stat mystat;
    DIR * mydir;
    //Initialize buffer to store absolute file paths
    char buff [PATH_MAX + 1];
    //Open directory and check for error
    mydir = opendir(dirname);
    if (mydir == NULL) {
        perror("opendir");
        exit(1);
    }
    //Change directories
    chdir(dirname);
    //Read each entry in directory
    while ((myfile = readdir( mydir ) ) != NULL) {
        //lstat on each entry in directory
        int n = lstat(myfile->d_name, &mystat);
        //Check if lstat returns error
        if (n == 0) {
            //Check if user entered a seach substring
            if (str != NULL && str[0] == '\0' && checkType(mystat, type)) {
                //Make sure the current file is not .. or . if no search string is provided
                if (( strcmp(myfile->d_name, "..") != 0 ) && ( strcmp(myfile->d_name, ".") != 0 )) {
                    if ( (S_ISLNK(mystat.st_mode) != 0) ) { //Check for symlink
                        //get absolute path of pwd and cat with the sym file before printing
                        char * absPath = getcwd(buff, PATH_MAX + 1);
                        strcat(absPath, myfile->d_name);
                        puts(absPath);
                    } else {
                        //get absolute path and print if not symlink
                        char * absPath = realpath(myfile->d_name, buff);
                        puts(absPath);
                    }
                }
            } else {
                //If string is provided, check for matching files
                if (strstr(myfile->d_name, str) != NULL && checkType(mystat, type)) {
                    //Check if it is a symbolic link
                    if ( (S_ISLNK(mystat.st_mode) != 0 )) {
                        //get absolute path of pwd and cat with the sym file before printing
                        char * absPath = getcwd(buff, PATH_MAX + 1);
                        strcat(absPath, myfile->d_name);
                        puts(absPath);
                    } else {
                        //Print absolute path if it is not a symbolic link
                        char * absPath = realpath(myfile->d_name, buff);
                        puts(absPath);
                    }
                }
            }

            //Recursively search directories if the current file is not . or ..
            if ( ( strcmp(myfile->d_name, "..") != 0 ) && ( strcmp(myfile->d_name, ".") != 0 ) ) {
                //Check if file is directory
                if (isdirectory(myfile->d_name)) {
                    //Check directory permissions
                    if (testPerms(myfile->d_name, 5)) {
                        //Allocate memory for new directory search
                        char * newdirname = (char *) malloc((strlen(myfile->d_name) + 1)* sizeof(char));
                        strcpy(newdirname, myfile->d_name);
                        //printf("Recursive call on dir: %s\n", newdirname); //debugging
                        //Start recursive search on new directory
                        searchdir(newdirname, str, type);
                        //Free allocated memory
                        free(newdirname);
                        //Change back to parent directory after recursive search
                        chdir("..");
                    } else {
                        //Print error for permission denied
                        char * absPath = realpath(myfile->d_name, buff);
                        perror(absPath);
                    }
                }
            }
        } else {
            perror("lstat on file error");
            exit(1);
        }
    }
    //Close directory
    closedir(mydir);

}
