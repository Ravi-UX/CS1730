#ifndef CHUNK_H
#define WAGERS_H

extern void lineParse(char * file, int parse, char * prefix, char * suffix);
extern void wordParse(char * file, int parse, char * prefix, char * suffix);
extern void charParse(char * file, int parse, char * prefix, char * suffix);
extern char * mkFileName(char * prefix, char * suffix);

#endif
