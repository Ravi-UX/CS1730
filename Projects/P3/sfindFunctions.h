#ifndef SFIND_H
#define SFINDFUNCTIONS_H

extern int isdirectory( char * filename );
extern int testPerms( char * filename, int perms);
extern void searchdir( char * dirname, char * str, char type);
extern int checkType(struct stat mystat, char type);

#endif
