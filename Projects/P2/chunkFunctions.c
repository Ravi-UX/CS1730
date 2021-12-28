#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

/*
 * Helper function to create a new suffix for file name
 * Precondition: Valid suffix is provided
 * Postcondition: a suffix is returned
 * Parameter: a suffix of type (char *)
 * returns: a suffix
 */
char * mkSuffix(char * suffix) {
    //Break suffix into 2 chars
    char c1 = suffix[0];
    char c2 = suffix[1];
    char * suff = malloc(3 * sizeof(char));
    //Check if the suffix is alphabetical
    if ((int)c1 >= (int)'a' && (int)c1 <= (int)'z') {
        //CHeck if second char of suffix needs to be incremented
        if ((int)c2 < (int)'z') {
            c2++;
            char temp[3] = {c1, c2, '\0'};
            strcpy(suff, temp);
            return suff;
        } else {
            //Checks if first char of suffix needs to be incremented
            if ((int)c1 < (int)'z') {
                c1++;
                c2 = 'a';
                char temp[3] = {c1, c2, '\0'};
                strcpy(suff, temp);
                return suff;
            } else {
                char temp[3] = {'z', 'z', '\0'};
                strcpy(suff, temp);
                return suff;
            }
        }
    }
    //Check if the suffix is numerical
    if ((int)c1 >= (int)'0' && (int) c1 <= (int)'9') {
        //Check if second char of suffix needs to be incremented
        if ((int)c2 < (int)'9') {
            c2++;
            char temp[3] = {c1, c2, '\0'};
            strcpy(suff, temp);
            return suff;
        } else {
            //Check if first char of suffix needs to be incremented
            if ((int)c1 < (int)'9') {
                c1++;
                c2 = '0';
                char temp[3] = {c1, c2, '\0'};
                strcpy(suff, temp);
                return suff;
            } else {
                char temp[3] = {'9','9','\0'};
                strcpy(suff, temp);
                return suff;
            }
        }
    }
    return suff;
}

/*
 * Funciton to split a file into multiple files based on number of lines
 * Pre condition: a file name, an int, a prefix, and suffix are passed in
 * Post condition: The files are parsed based on the number of lines specified
 * Parameters: file, parse, prefix, suffix
 * Returns: void
 */
void lineParse(char * file, int parse, char * prefix, char * suffix) {
    int input_fd, output_fd; //File descriptors for read and write
    ssize_t return_num_bytes_read, //Store bytes read and write
        return_num_bytes_write;
    char * buffer; //Buffer to read and write from

    //Line count
    register int lc = 0;

    buffer = (char *) calloc(1, sizeof(char));
    //Init input_fd
    if (file != NULL) {
        input_fd = open(file, O_RDONLY);
    } else {
        input_fd = 0;
    }
    //Create string for new file name
    char * temp = &(*suffix);
    char fName[strlen(prefix) + 3];
    strcpy(fName, prefix);
    temp = mkSuffix(temp);
    strcat(fName, temp);
    //Init output_fd
    output_fd = open(fName, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if(output_fd == -1) {
        fprintf(stderr, "file name already exists\n");
        exit(1);
    }
    //Read and write to file
    while ((return_num_bytes_read = read(input_fd, buffer, 1)) > 0) {
        if (return_num_bytes_read == -1) {
            fprintf(stderr, "read error: invalid file or file not provided\n");
            exit(1);
        }
        //Write and Create new file if line count limit is reached
        if (lc == parse) {
            /*return_num_bytes_write = write(output_fd, buffer, (ssize_t) return_num_bytes_read);
            if (return_num_bytes_write != return_num_bytes_read) {
                fprintf(stderr, "write error");
                exit(1);
                }*/
            lc = 0;
            close(output_fd);
            char name[strlen(prefix) + 3];
            strcpy(name, prefix);
            temp = mkSuffix(temp);
            strcat(name, temp);
            output_fd = open(name, O_WRONLY | O_CREAT | O_EXCL, 0644);
            if(output_fd == -1) {
               fprintf(stderr, "file name already exists");
               exit(1);
            }
        }
        return_num_bytes_write = write(output_fd, buffer, (ssize_t) return_num_bytes_read);
        if (return_num_bytes_write != return_num_bytes_read) {
            fprintf(stderr, "write error");
            exit(1);
        }

        if (buffer[0] == '\n') {
            lc++;
        }

    }
    close(input_fd);
    close(output_fd);
}

/*
 * Function to break a file into multiple files based on number of words
 * Pre condition: a file name, number of words per file, a prefix, and a suffix are passed in
 * Post condition: File provided is split into multiple files based on number of words
 * Parameters: file, parse, prefix, suffix
 * Returns: void
 */
void wordParse(char * file, int parse, char * prefix, char * suffix) {
    int input_fd, output_fd; //File descriptors for read and write
    ssize_t return_num_bytes_read, //Store bytes read and write
        return_num_bytes_write;
    char * buffer; //Buffer to read to and write from

    //Word count
    register int wc = 0;

    buffer = (char *) calloc(1, sizeof(char));
    //Init input_fd
    if (file != NULL) {
        input_fd = open(file, O_RDONLY);
    } else {
        input_fd = 0;
    }
    char * temp = &(*suffix);
    //Loop until EOF
    while(1) {
        //Create a string to be used for new file
        char fName[strlen(prefix) + 3];
        strcpy(fName, prefix);
        temp = mkSuffix(temp);
        strcat(fName, temp);
        output_fd = open(fName, O_WRONLY | O_CREAT | O_EXCL, 0644);
        if(output_fd == -1) {
            fprintf(stderr, "file name already exists\n");
            exit(1);
        }
        //Read and write to new file
        while (wc < parse && (return_num_bytes_read = read(input_fd, buffer, 1)) > 0) {
            if (return_num_bytes_read == -1) {
                fprintf(stderr, "read error: invalid file or file not provided\n");
                exit(1);
            }
            return_num_bytes_write = write(output_fd, buffer, (ssize_t) return_num_bytes_read);
            if (return_num_bytes_write != return_num_bytes_read) {
                fprintf(stderr, "write error");
                exit(1);
            }
            //Check if character read is printable
            if(isgraph(buffer[0])) {
                //If printable, then it is a word
                wc++;
                //Do until the end of the word is reached
                do {
                    return_num_bytes_read = read(input_fd, buffer, 1);
                    if (return_num_bytes_read == 0) {
                        break;
                    }
                    if (return_num_bytes_read == -1) {
                        fprintf(stderr, "read error\n");
                        exit(1);
                    }
                    return_num_bytes_write = write(output_fd, buffer, (ssize_t) return_num_bytes_read);
                    if (return_num_bytes_write != return_num_bytes_read) {
                        fprintf(stderr, "write error\n");
                        exit(1);
                    }
                } while (isgraph(buffer[0]));
            }
        }
        wc = 0;
        close(output_fd);
        if (return_num_bytes_read < 1) {
            break;
        }
    }
    close(input_fd);
    close(output_fd);
}

/*
 * Function to split a file based on number of characters
 * Pre condition: file, number of chars per file, prefix, and suffix are provided
 * Post conditions: File is split based on number of chars
 * Parameters: file, parse, prefix, suffix
 * Returns: void
 */
void charParse(char * file, int parse, char * prefix, char * suffix) {
    int input_fd, output_fd; //Input and output file descriptors
    ssize_t return_num_bytes_read, //Store num byes read and write
        return_num_bytes_write;
    char * buffer; //Buffer to read to and write from

    register int cc = 0; //Character count
    buffer = (char *) calloc(1, sizeof(char));
    //Init file descriptor
    if (file != NULL) {
        input_fd = open(file, O_RDONLY);
    } else {
        input_fd = 0;
    }
    char * temp = &(*suffix);
    //Loop until all necessary files are created
    while(1) {
        //Create a string to name the new files
        char fName[strlen(prefix) + 3];
        strcpy(fName, prefix);
        temp = mkSuffix(temp);
        strcat(fName, temp);
        //Open new file
        output_fd = open(fName, O_WRONLY | O_CREAT | O_EXCL, 0644);
        if (output_fd == -1) {
            fprintf(stderr, "file name already exists\n");
            exit(1);
        }
        //Read and write to new file
        while (cc < parse && (return_num_bytes_read = read(input_fd, buffer, 1)) > 0) {
            if (return_num_bytes_read == -1) {
                fprintf(stderr, "read error: invalid file or file not provided\n");
                exit(1);
            }
            cc++;
            return_num_bytes_write = write(output_fd, buffer, (ssize_t) return_num_bytes_read);
            if (return_num_bytes_write != return_num_bytes_read) {
                fprintf(stderr, "write error");
                exit(1);
            }
        }
        cc = 0;
        close(output_fd);
        //Break when EOF
        if (return_num_bytes_read < 1) {
            break;
        }
    }
    close(input_fd);
    close(output_fd);
}
