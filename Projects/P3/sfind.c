#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

#include <string.h>
#include <linux/limits.h>
#include "sfindFunctions.h"

/**
 * Main method for sfind
 */
int main(int argc, char * argv[]) {
    char * startDir = "."; //Starting directory
    char * str = ""; //Initial substring to be searched for
    char type = '\0';
    int opt;
    while((opt = getopt(argc, argv, ":s:n:t:")) != -1) {
        //Switch statement to capture each commandline arg
        switch(opt) {
            //Store directory name
            case 's':
                startDir = optarg;
                break;
            //Store search substring
            case 'n':
                str = optarg;
                break;
            //Store file type
            case 't':
                type = optarg[0];
                break;
            case ':':
                perror("option needs a value\n");
                exit(1);
            case '?':
                perror("unknown option\n");
                exit(1);
        }//switch
    }//while

    //Test if directory
        if( ! isdirectory( startDir ) ) {
            perror("it is not a directory\n" );
            exit(1);
        }//if

        //Initialize buffer for full path
        char buff [PATH_MAX + 1];
        struct stat mystat;
        char * absPath = realpath(startDir, buff);
        //lstat() on initial directory
        int n = lstat(startDir, &mystat);
        // Check for error
        if (n == 0) {
            //Check if search string was provided
            if (str != NULL && str[0] == '\0' && checkType(mystat, type)) {
                puts(absPath);
            } else { //if
                if (strstr(startDir, str) != NULL && checkType(mystat, type)) {
                    puts(absPath);
                } //if
            } //else
        } else {//if
            perror("lstat on starting directory error");
        }//else

        //Check if directory has permissions to read and execute
        if (! testPerms( startDir, 5 ) ) {
            perror(absPath);
            exit(1);
        }
        //Start the search on the directory
        searchdir(startDir, str, type);




    return 0;
}
