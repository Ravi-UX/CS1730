//  Created by Maria Hybinette on 10/07/14
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (void )
{
    pid_t child_pid;
    printf ("the main program process ID is %d\n", (int) getpid ());
    
    child_pid = fork();
    if( child_pid > 0 ) // parent processes this
    {
        printf( "me=parent my PID is  %d\n", (int) getpid () );
        printf( "me=parent fork returned %d\n", (int) child_pid );
    }
    else
        printf( "me=child  getpid=%d fork returned %d\n" , (int) getpid (), child_pid);
    return 0;
}


