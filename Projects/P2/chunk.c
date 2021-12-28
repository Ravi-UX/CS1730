#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

#include <string.h>
#include "chunkFunctions.h"

/*
 * Main method for program.
 * Captures comand line args and calls functions accordingly
 * Preconditions: N/A
 * Post Conditions: 0 is returned
 */
int main(int argc, char * argv[]) {
    int opt; //Variable to loop through all options
    int count = 0; //Count to make sure multiple options are not provided
    int option = 'z'; //Captures l, w, or c options
    char * file = '\0'; //provided file
    char * prefix = "x"; //Default suffix
    char * suffix = "a`"; //Default prefix
    int parse; //Number items per file
    //Loop through provided options
    while((opt = getopt(argc, argv, ":l:w:c:f:p:s:")) != -1) {
        //Switch statement to capture each commandline arg
        switch(opt) {
            case 'l':
                if (count >= 1) {
                    fprintf(stderr, "invalid args\n");
                    exit(1);
                }
                option = 'l';
                parse = atoi(optarg);
                count++;
                break;
            case 'w':
                if (count >= 1) {
                    fprintf(stderr, "invalid args\n");
                    exit(1);
                }
                option = 'w';
                parse = atoi(optarg);
                count++;
                break;
            case 'c':
                if (count >= 1) {
                    fprintf(stderr, "invalid args\n");
                    exit(1);
                }
                option = 'c';
                parse = atoi(optarg);
                count++;
                break;
            case 'f':
                file = optarg;
                break;
            case 'p':
                prefix = optarg;
                break;
            case 's':
                suffix = optarg;
                break;
            case ':':
                fprintf(stderr,"option needs a value\n");
                exit(1);
            case '?':
                fprintf(stderr,"unknown option: %c\n", optopt);
                exit(1);
        }
    }
    if (parse < 1) {
        fprintf(stderr,"enter a number greater than 0\n");
        exit(1);
    }
    //Make a function call based on what option is provided
    switch(option) {
        case 'l':
            lineParse(file, parse, prefix, suffix);
            break;
        case 'w':
            wordParse(file, parse, prefix, suffix);
            break;
        case 'c':
            charParse(file, parse, prefix, suffix);
            break;
        default:
            fprintf(stderr,"options: l, w, or c needed");
            exit(1);
    }



    return 0;
}
