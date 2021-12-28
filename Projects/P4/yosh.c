
/* -----------------------------------------------------------------------------
FILE: yosh.c

NAME: Ravi Cheekati

DESCRIPTION: A BASIC SHELL
-------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wordexp.h>
#include <linux/limits.h>
#include "parse.h"   // local file include declarations for parse-related structs

//enum BUILTIN_COMMANDS { NO_SUCH_BUILTIN=0, EXIT, JOBS, CD, HISTORY, KILL, HELP};

//A linked list where each node represents a process
struct Node {
    int num;
    char *cmd;
    pid_t pid;
    int mode;
    struct Node *next;
};
//Initialize linked list
struct Node *head;
struct Node *tail;
//Number of active jobs
int active;
/* -----------------------------------------------------------------------------
FUNCTION: buildPrompt()
DESCRIPTION: Builds the prompt for the yosh shell
returns a string containing the prompt
-------------------------------------------------------------------------------*/
char * buildPrompt() {
    //Allocate memory for prompt
    char * prompt = (char*) malloc(PATH_MAX + 7);
    char cwd [PATH_MAX];
    //Get cwd and append it to the prompt
    getcwd(cwd, PATH_MAX);
    strcpy(prompt, "yosh:");
    strcat(prompt, cwd);
    strcat(prompt, "% ");

    //Return the prompt
    return prompt;
}

/* -----------------------------------------------------------------------------
FUNCTION: isBuiltInCommand(char * cmd)
DESCRIPTION: Checks if the parameter cmd is a built in command
returns 1 if built in command and 0 if not
-------------------------------------------------------------------------------*/
int isBuiltInCommand( char * cmd ) {
    //Check if cmd is a built in command
  if( strncmp(cmd, "exit", strlen( "exit" ) ) == 0 )
	{
        return 1;
  	}
  if ( strncmp(cmd, "jobs", strlen( "jobs" ) ) == 0 )
      return 1;

  if ( strncmp(cmd, "cd", strlen( "cd" ) ) == 0 )
      return 1;

  if ( strncmp(cmd, "history", strlen( "history" ) ) == 0 )
      return 1;


  if ( strncmp(cmd, "kill", strlen( "kill" ) ) == 0 )
      return 1;

  if ( strncmp(cmd, "help", strlen( "help" ) ) == 0  )
      return 1;

  return 0;
}

/*
 * Gets the job based on the number of the job
 * Takes an the job number n as a parameter
 * Returns the Node which contains the target job or NULL
 */
struct Node *getJob(int n) {
    struct Node *curr = (struct Node*) malloc(sizeof(struct Node));
    //Search through linked list for the job
    for (curr = head; curr != NULL; curr = curr->next) {
        if (n == curr -> num) {
            return curr;
        }
    }
    return NULL;
}


/*
 * Execute the built in command.
 * The parameters are cmd (the command), argv(the arguments), argc (the number of arguments),
 * and head (the head of a list containing all running jobs)
 * Returns 1 on success
 */
int executeBuiltInCommand(char *cmd, char **argv, int argc) {
    //Exit command
    if (strncmp(cmd, "exit", strlen( "exit" ) ) == 0) {
        if (active != 0) {
            printf("There are still jobs running");
            return 0;
        }
        exit(0);
    }
    //History command
    if ( strncmp(cmd, "history", strlen( "history" ) ) == 0 ) {
        register HIST_ENTRY ** hist_list;
        register int i;
        //Print the command history
        hist_list = history_list();
        if (hist_list) {
            for (i = 0; hist_list[i]; i++) {
                printf ("%s\n",hist_list[i] -> line);
            }
        }
    }

    //Jobs command
    if ( strncmp(cmd, "jobs", strlen( "jobs" ) ) == 0 ) {
        if (head != NULL) {
            char *md = (char *) malloc(sizeof(char) * 11);
            struct Node* job = (struct Node*) malloc(sizeof(struct Node));
            int i = 1;
            //Loop through all jobs in the linked list
            for (job = head; job != NULL; job = job -> next) {
                //Check if the job is finished
                if (job -> mode == 3) {
                    if (job != head) {
                        if (job->next != NULL) {
                            getJob(i - 1) -> next = job -> next;
                        } else {
                            getJob(i - 1) -> next = NULL;
                            free(job);
                        }
                    } else {
                        if (job -> next != NULL) {
                            head = job -> next;
                            free(job);
                        } else {
                            free(job);
                            head = NULL;
                            tail = NULL;
                            break;
                        }
                    }
                    continue;
                } else {
                    //Check if job is terminated
                    if (job -> mode == 2) {
                        strcpy(md, "Terminated");
                        job -> mode = 3;
                    } else {
                        //check if job is running
                        if (kill(job -> pid, 0) == 0) {
                            strcpy(md, "Running");
                        } else {
                            //Job is done
                            strcpy(md, "Done");
                            job -> mode = 3;
                        }
                    }
                    //Print the job
                    job -> num = i;
                    i++;
                    tail = job;
                    printf("[%d]\t%d\t%s\t%s\n", job -> num, job -> pid, md, job -> cmd);
                }
            }
        }
        return 1;
    }

    //cd command
    if ( strncmp(cmd, "cd", strlen( "cd" ) ) == 0 ) {
        wordexp_t result;
        char * arg = argv[1];
        //Check if cd got passed any arguments
        if (arg == NULL) {
            arg = "~";
        }
        //Expand the argument passed to cd
        wordexp(arg, &result, 0);
        char ** words = result.we_wordv;
        //Change the directory
        chdir(words[0]);
        wordfree(&result);
        return 1;
    }

    //help command
    if ( strncmp(cmd, "help", strlen( "help" ) ) == 0  ) {
        //Print all built in commands and the syntax
        printf("jobs\n");
        printf("cd [directory name]\n");
        printf("history\n");
        printf("exit\n");
        printf("kill %%num\n");
        printf("help\n");
        return 1;
    }
    //kill command
    if ( strncmp(cmd, "kill", strlen( "kill" ) ) == 0 ) {
        //Check number of arguments
        if (argc < 2) {
            fprintf(stderr, "Usage: Kill %%number\n");
            return 0;
        }
        //CHeck args
        if (strlen(argv[1]) < 1) {
            fprintf(stderr, "Usage: Kill %%number\n");
            return 0;
        }
        //Parse the argument for job number
        struct Node* curr;
        if (argv[1][0] == '%') {
            int id = atoi(argv[1] + 1);
            curr = getJob(id);
        } else {
            int pid = atoi(argv[1]);
            for (curr = head; curr != NULL; curr = curr -> next) {
                if (pid == curr -> pid) {
                    break;
                }
            }
        }
        //Kill the job
        if (curr == NULL) {
            fprintf(stderr, "yosh: kill: [%s] - No such process\n", argv[1]);
        } else {
            if (kill(curr -> pid, SIGKILL) < 0) {
                perror("kill");
            } else {
                printf("Killed: %d\n", curr -> pid);
            }
        }


        return 1;
    }
    return 0;
}

/*
 * Signal for back ground jobs
 * Takes a signal s as a parameter
 */
void handle_sigchld( int s )
{
    /* execute non-blocking waitpid, loop because we may only receive
     * a single signal if multiple processes exit around the same time.
     */
    while( waitpid(0, NULL, WNOHANG) > 0) ;
    //Decrease the number of active jobs
    active --;
}

/*
 * Sets the appropriate file descriptors for the process in order to pipe
 * Takes the argument array argv of the command, the readfd of the pipe,
 * and the write fd of the pipe as parameters
 */
void setProcessfd(char **argv, int readfd, int writefd) {
    //Create a new child process to read and wrtie from pipe
    if (fork() == 0) {
        //replace stdin of the process with readfd
        if (readfd != STDIN_FILENO) {
            dup2(readfd, STDIN_FILENO);
            close(readfd);
        }
        //Replace stdout of the process with writefd
        if (writefd != STDOUT_FILENO) {
            dup2(writefd, STDOUT_FILENO);
            close(writefd);
        }
        //execute chile process
        execvp(argv[0], argv);
    }

    wait(NULL);

}


/* -----------------------------------------------------------------------------
FUNCTION: main()
DESCRIPTION:
-------------------------------------------------------------------------------*/
int main( int argc, char **argv )
{
  char * cmdLine;
  parseInfo *info; 		// info stores all the information returned by parser.
  struct commandType *com; 	// com stores command name and Arg list for one command.
  int childPid;
  head = NULL;
  tail = NULL;
  active = 0;


  fprintf( stdout, "This is Yo Shell version 0.1\n" ) ;
  signal( SIGCHLD, handle_sigchld );

  while(1) {

    	//Read in the user input
    	cmdLine = readline( buildPrompt() ) ;
    	if( cmdLine == NULL ) {
      		fprintf(stderr, "Unable to read command\n");
      		continue;
    	}

    	// Initialize history data structure
        char *expansion;
        int result;
        using_history();
        //Cap the size of the list to 10
        stifle_history(10);
        //expand the user input and store in to expansion
        history_expand(cmdLine, &expansion);
        //add command to list
        add_history(expansion);
        //copy expansion to input string
        //wordexp_t  exp;
        //wordexp(cmdLine, &exp, 0);
        //char ** words = exp.we_wordv;
        strncpy(cmdLine, expansion, sizeof(cmdLine) - 1);
        //free(words);
        free(expansion);

    	// calls the parser
    	info = parse( cmdLine );
        if( info == NULL )
	{
      		free(cmdLine);
      		continue;
    	}

    	// prints the info struct
    	//print_info( info );

    	//com contains the info. of the command before the first "|"
    	com = &info->CommArray[0];
    	if( (com == NULL)  || (com->command == NULL))
    	{
      		free_info(info);
      		free(cmdLine);
      		continue;
    	}

    	//com->command tells the command name of com
        //Check if built in command
    	if( isBuiltInCommand( com->command ) == 1 ) {
            executeBuiltInCommand(com -> command, com -> VarList, com -> VarNum);
    	} else {
            int readfd = STDIN_FILENO;
            //Fork if it is a UNIX command
            childPid = fork();
            if ( childPid == 0 ) {
                //Setup input redirection
                if (info -> boolInfile)
                    dup2(open(info -> inFile, O_RDWR|O_CREAT,0777),0);
                //Setup output redirection
                if (info -> boolOutfile)
                    dup2(open(info -> outFile, O_RDWR|O_CREAT,0777),1);

                if (info -> pipeNum > 0) {
                    //Setup for piping
                    int fds[2];
                    int i;
                    //Change the fds for each command's process and execute them
                    for (i = 0; i < info -> pipeNum; ++i) {
                        pipe(fds);
                        com = &info->CommArray[i];
                        setProcessfd( com -> VarList, readfd, fds[1] );
                        readfd = fds[0];
                        close(fds[1]);
                    }
                    //Execute the final command after reading from pipe
                    if (readfd != 0)
                        dup2(readfd, 0);
                    com = &info->CommArray[i];
                    execvp(com -> command, com -> VarList);

                } else {
                    //Execute command if no piping
                     execvp(com -> command, com -> VarList);
                }
            } else {
                if (info->boolBackground == 1) {
                    active++;
                    //Store in list of background processes and continue
                    char *command = (char *) malloc(NAME_MAX);
                    struct Node* job = (struct Node*) malloc(sizeof(struct Node));
                    strcpy(command, "");
                    int i = 0;
                    while (com -> VarList[i] != NULL) {
                        strcat(command, com->VarList[i]);
                        strcat(command, " ");
                        i++;
                    }
                    //Populate the node struct
                    job -> cmd = command;
                    job -> pid = childPid;
                    job -> mode = 0;
                    job -> next = NULL;
                    int numJobs = 1;
                    if (head != NULL) {
                        //Calculate the job number
                        struct Node* curr = (struct Node*) malloc(sizeof(struct Node));
                        for (curr = head; curr != NULL; curr = curr -> next) {
                            numJobs++;
                        }
                        job -> num = numJobs;
                    } else {
                        //If head is null then the current job is the first job
                        job -> num = 1;
                        head = job;
                        tail = job;
                        continue;
                    }
                    tail -> next = job;
                    tail = job;
                    continue;
                } else {
                    //If not a backgroudn process, wait for child to terminate
                    waitpid(childPid, NULL, 0);
                }
            }
        }

  //insert your code here / commands etc.



  free_info(info);

  free(cmdLine);

  }/* while(1) */



}
