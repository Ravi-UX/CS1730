
/* -----------------------------------------------------------------------------
FILE: shell.c
 
NAME:

DESCRIPTION: A SHELL SKELETON
-------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "parse.h" // local file include declarations for parse-related structs
#include "list.h"
#include <wait.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wordexp.h>
#include <limits.h>
#include <signal.h>

enum BUILTIN_COMMANDS
{
	NO_SUCH_BUILTIN = 0,
	EXIT,
	JOBS,
	HISTORY,
	KILL,
	CD,
	HELP
};

struct job {
	int num;
	char *command;
	pid_t pid;
	int mode;
	struct job *nextjob;
};

struct job *head;
struct job *tail;

/* -----------------------------------------------------------------------------
FUNCTION: buildPrompt()
DESCRIPTION:
-------------------------------------------------------------------------------*/
char *buildPrompt() {
	char * prompt = (char * ) malloc(PATH_MAX);
	char cwd[PATH_MAX];
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		strcpy(prompt, "{yosh}:");
		strcat(prompt, cwd);
		strcat(prompt, "$ ");
		return prompt;
	} else {
		perror("getcwd() error");
		exit(1);
	}
	
	
	return prompt;
}

int redirectionTester(parseInfo *info) {
	if (info->boolInfile) {
		if (info->boolInfile > 1) {
			fprintf(stderr, "Ambiguous input redirect.\n");
			return 0;
		}
		if (info->inFile[0] != '\0') {
			if( access(info->outFile, F_OK ) != 0 ) {
				dup2(open(info->inFile, O_RDWR|O_CREAT,0777),0);
			} else {
				fprintf(stderr, "%s: No such file or directory.\n", info->inFile);
				return 0;
			}
		} else {
			fprintf(stderr, "Missing name for redirect.\n");
			return 0;
		}
	}
	if (info->boolOutfile) {
		if (info->boolOutfile > 1) {
			fprintf(stderr, "Ambiguous output redirect.\n");
			return 0;
		}
		if (info->outFile[0] != '\0') {
			if( access(info->outFile, F_OK ) != 0 ) {
				dup2(open(info->outFile, O_RDWR|O_CREAT,0777),1);
			} else {
				fprintf(stderr, "%s: File exists.\n", info->outFile);
				return 0;
			}
		} else {
			fprintf(stderr, "Missing name for redirect.\n");
			return 0;
		}
	}
	return 1;
}

/* -----------------------------------------------------------------------------
FUNCTION: jobID(int getID)
DESCRIPTION: returns a job based on it's numerical ID. This assumes there exists
a job with an ID of the parameter getID. This returns the job with the ID of said
integer paramter, and returns NULL if that is not found before the loop 
terminates by reaching NULL through assigning temp to its own nextjob.
-------------------------------------------------------------------------------*/
struct job *jobID(int getID) {
	struct job *temp = (struct job*) malloc(sizeof(struct job)); // creates a temporary object to loop until the ID is found
	for (temp = head; temp != NULL; temp = temp->nextjob) {
		if (getID == temp->num) {
			return temp;
		}
	}
	return NULL;
}

/* -----------------------------------------------------------------------------
FUNCTION: isBuild()
DESCRIPTION:
-------------------------------------------------------------------------------*/
int isBuiltInCommand(char *cmd)
{
	if (strncmp(cmd, "exit", strlen("exit")) == 0) {
		return EXIT;
	}
	if (strncmp(cmd, "history", strlen("history")) == 0) {
		return HISTORY;
	}
	if (strncmp(cmd, "cd", strlen("cd")) == 0) {
		return CD;
	}
	if (strncmp(cmd, "help", strlen("help")) == 0) {
		return HELP;
	}
	if (strncmp(cmd, "jobs", strlen("jobs")) == 0) {
		return JOBS;
	}
	if (strncmp(cmd, "kill", strlen("kill")) == 0) {
		return KILL;
	}
	return NO_SUCH_BUILTIN;
}

/* -----------------------------------------------------------------------------
FUNCTION:int executeBuiltInCommand(char *command, char **argv) {
DESCRIPTION:
-------------------------------------------------------------------------------*/
int executeBuiltInCommand(char *command, char ** argv, int out) {
	if (isBuiltInCommand(command) == HISTORY) { // the history command
		fprintf(stderr, "making history\n");
		register HIST_ENTRY ** hist_list;
		register int i;
		time_t tt;
		FILE* fp; // only useful when built-in commands are being piped
		char timestr[128];

		hist_list = history_list();
		if (hist_list) {
			if (out != 0)
				fp = fdopen(out, "w"); // creates a file stream if a pipe exists and history is to redirect it's own output
			for (i = 0; hist_list[i]; i++) {
				tt = history_get_time (hist_list[i]);

				if (tt)
					strftime (timestr, sizeof (timestr), "%a %R", localtime(&tt));
				else
					strcpy (timestr, "??");

				if (out != 0) { // occurs if the intended output is not standard output
					fprintf (fp, "%.4d: %s: %s\n", i + history_base, timestr, hist_list[i]->line);
				} else { // occurs when the intended output is standard output
					printf ("%.4d: %s: %s\n", i + history_base, timestr, hist_list[i]->line);
				}
			}
			if (out != 0) { // breaks out if pipes are involved
				exit(0);
			}
			return 0;
		}
	} else if (isBuiltInCommand(command) == CD) { // the cd command
		int count = 0; 
		while(argv[++count] != NULL);
		if (count < 2) {
			fprintf (stderr, "Usage: CD destination\n");
			if (out != 0) { // breaks out if pipes are involved
				exit(0); // exits and kills the child process
			}
			return 0;
		}
		wordexp_t result;
		char * loc = argv[1];
		
		if (loc == NULL) {
			loc = "~";
		}
		wordexp(loc, &result, 0);
		char ** words = result.we_wordv;
		chdir(words[0]);;
		wordfree(&result);
		
		return 0;
	} else if (isBuiltInCommand(command) == HELP) { // the help command
		if (out != 0) {
			FILE* fp; // only useful when built-in commands are being piped
			fp = fdopen(out, "w"); // creates a file stream if a pipe exists and help is to redirect it's own output
			fprintf (fp, "jobs\ncd [directory name]\nhistory\nexit\nkill [num or %%num]\nhelp\n");
			exit(0); // breaks out if pipes are involved
		}
		printf("jobs\ncd [directory name]\nhistory\nexit\nkill [num or %%num]\nhelp\n");
		return 0;
	} else if (isBuiltInCommand(command) == JOBS) { // the jobs command
		if (head != NULL) {
			FILE* fp; // only useful when built-in commands are being piped
			if (out != 0) {
				fp = fdopen(out, "w"); // creates a file stream if a pipe exists and help is to redirect it's own output
			}
			char *mode = (char *) malloc(sizeof(char) * 11);
			struct job *jobstruct = (struct job*) malloc(sizeof(struct job));
			int i = 1;
			for (jobstruct = head; jobstruct != NULL; jobstruct = jobstruct->nextjob) {
				if (jobstruct->mode == 3) {
					if (jobstruct != head) {
						if (jobstruct->nextjob != NULL) {
							jobID(i - 1)->nextjob = jobstruct->nextjob;
						} else {
							jobID(i - 1)->nextjob = NULL;
							free(jobstruct);
						}
					} else {
						if (jobstruct->nextjob != NULL) {
							head = jobstruct->nextjob;
							free(jobstruct);
						} else {
							free(jobstruct);
							head = NULL;
							tail = NULL;
							break;
						}
					}
					continue;
				}
				else if (jobstruct->mode == 2) {
					strcpy(mode, "Terminated");
					jobstruct->mode = 3;
				} else {
					if (kill(jobstruct->pid, 0) == 0) {
						strcpy(mode, "Running");
					}
					else {
						strcpy(mode, "Done");
						jobstruct->mode = 3;
					}
				}
				jobstruct->num = i; // sets the id of jobstruct
				i++; // incriments here to prevent cleared jobs from interfering
				tail = jobstruct; // sets tail to jobstruct
				//free(jobstruct);
				if (out != 0) { // breaks out if pipes are involved
					fprintf (fp, "[%d]\t%d\t%s\t%s\n", jobstruct->num, jobstruct->pid, mode, jobstruct->command);
				}
				printf("[%d]\t%d\t%s\t%s\n", jobstruct->num, jobstruct->pid, mode, jobstruct->command);
			}
		}
		if (out != 0) { // breaks out if pipes are involved
			exit(0); // exits and kills the child process
		}
		return 0;



	} else if (isBuiltInCommand(command) == KILL) { // the kill command
		int count = 0; 
		while(argv[++count] != NULL);
		if (count < 2) {
			fprintf (stderr, "Usage: Kill %%number\n");
			if (out != 0) { // breaks out if pipes are involved
				exit(0); // exits and kills the child process
			}
			return 0;
		}
		if (strlen(argv[1]) < 1) {
			fprintf (stderr, "Usage: Kill %%number\n");
			if (out != 0) { // breaks out if pipes are involved
				exit(0); // exits and kills the child process
			}
			return 0;
		}
		struct job *tempjob = (struct job*) malloc(sizeof(struct job)); // tempjob for finding size
		if (argv[1][0] == '%') {
			int id = atoi(argv[1] + 1);
			tempjob = jobID(id);
		} else { 
			int pid = atoi(argv[1]);
			for (tempjob = head; tempjob != NULL; tempjob = tempjob->nextjob) {
				if (pid == tempjob->pid) {
					break;
				}
			}
		}
		if (tempjob == NULL) {
			fprintf (stderr, "yosh: kill: (%s) - No such process\n", argv[1]);
		} else {
			if (kill(tempjob->pid, SIGKILL) < 0) {
				perror("kill");
			} else {
				if (out != 0) {
					FILE* fp; // only useful when built-in commands are being piped
					fp = fdopen(out, "w"); // creates a file stream if a pipe exists and help is to redirect it's own output
					fprintf(fp, "Process killed: %d\n", tempjob->pid);
				}
				printf("Process killed: %d\n", tempjob->pid);
			}
		}
		free(tempjob);
		if (out != 0) { // breaks out if pipes are involved
			exit(0); // exits and kills the child process
		}
		return 0;
 	} else if (isBuiltInCommand(command) == EXIT) { // the exit command
		exit(0);
	}
	return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION: void executeCommand(char *command, char **argv) {
DESCRIPTION:
-------------------------------------------------------------------------------*/
int executeCommand(char *command, char **argv) {
	if (isBuiltInCommand(command)) {
		return executeBuiltInCommand(command, argv, 1);
	}
	return execvp(command, argv);
}

void handle_sigchld( int s )
{
    /* execute non-blocking waitpid, loop because we may only receive
     * a single signal if multiple processes exit around the same time.
     */
    while( waitpid(0, NULL, WNOHANG) > 0) ;
}

/* -----------------------------------------------------------------------------
FUNCTION: int pipingHandler(char ** argv , int in, int out) {
DESCRIPTION:
-------------------------------------------------------------------------------*/
int pipingHandler(char ** argv , int in, int out) {
	int pid;
	if ((pid = fork()) == 0) { // forks for piping
		
		if (in != 0) {
			dup2(in, STDIN_FILENO); // makes sure standard input is sent to fds[0] or the start of the pipe
			close(in);
		}

		if (out != 1) {
			dup2(out, STDOUT_FILENO); // makes sure standard output is sent to fds[1] or the end of the pipe
			close(out);
		}
		fprintf(stderr, "Forking\n");
		
		if (!isBuiltInCommand(argv[0])) {
			return execvp(argv[0], argv); // runs execvp for non-built in commands
		} else { // occurs when the command is not built in
			return executeBuiltInCommand(argv[0], argv, 1);
		}
	}
	waitpid(pid, NULL, 0);
	return pid;
}

/* -----------------------------------------------------------------------------
FUNCTION: main()
DESCRIPTION:
-------------------------------------------------------------------------------*/
int main(int argc, char **argv) {
	parseInfo *info;		 // info stores all the information returned by parser.
	struct commandType *com; // com stores command name and Arg list for one command.
	
	head = NULL;
	tail = NULL;

	char *cmdLine;
	pid_t childPid;
	int status; // A pointer to the location where status information for the terminating process is to be stored

	int fds[2];
	int new_desc;

	fprintf(stdout, "This is the YOSH version 0.1\n");

	signal(SIGCHLD, handle_sigchld);

	while (1) {
		// insert your code here

		cmdLine = readline(buildPrompt());
		if (cmdLine == NULL) {
			fprintf(stderr, "Unable to read command\n");
			continue;
		}

		// insert your code about history and !x !-x here
		char *buffer;
		int result;
		using_history();
		stifle_history(10);
		history_expand(cmdLine, &buffer);
		add_history(buffer);
		strncpy(cmdLine, buffer, sizeof(cmdLine) - 1);
		free(buffer);


		// calls the parser
		info = parse(cmdLine);
		if (info == NULL) {
			free(cmdLine);
			continue;
		}

		// prints the info struct
		print_info(info);

		//com contains the info. of the command before the first "|"
		com = &info->CommArray[0];
		if ((com == NULL) || (com->command == NULL)) {
			free_info(info);
			free(cmdLine);
			continue;
		}
	
		//insert your code here / commands etc.

		//com->command tells the command name of com
		else if (info->pipeNum == 0 && isBuiltInCommand(com->command)) {
			int childNeeded = 0;
			if (info->boolInfile || info->boolOutfile) {
				childNeeded = 1; // determines if a fork is needed for input redir purposes
			}
			if (childNeeded == 1) {
				childPid = fork(); // creates the fork to allow dup2 to function properly
				if (childPid == 0) {
					if (redirectionTester(info) == 0) { // tests and implements input redirection
						continue; // exits preemptively before commands are run
					}
					executeBuiltInCommand(com->command, com->VarList, 1); //calls execvp
				}
				waitpid(childPid, NULL, 0);
			} else {
				executeBuiltInCommand(com->command, com->VarList, 0); //calls execvp
			}
		} else {
			childPid = fork();
			if (childPid == 0) {
				if (redirectionTester(info) == 0) { // tests and implements input redirection
					continue; // exits preemptively before commands are run
				}
				new_desc = 0; // sets the starting input to standard input
				if (info->pipeNum > 0) {
					int i;
					for (i=0; i < info->pipeNum; ++i) {
						pipe(fds);
						pipingHandler((&(info->CommArray[i]))->VarList, new_desc, fds[1]);
						close(fds[1]);
						new_desc = fds[0];
					}
					if (new_desc != 0)
						dup2(new_desc, 0);
					
					executeCommand((&(info->CommArray[i]))->command, (&(info->CommArray[i]))->VarList); //calls execvp
				} else {
					executeCommand(com->command, com->VarList); //calls execvp
				}
			} else {
				if (info->boolBackground)  { // TODO -- if( isBackgroundJob( cmd ) )
					int i = 0;
					int numjobs = 1;
					char *fullcommand = (char *) malloc(NAME_MAX);
					struct job *newjob = (struct job*) malloc(sizeof(struct job)); // creates a job object newjob
					strcpy(fullcommand, "");
					while(com->VarList[i] != NULL) {
						strcat(fullcommand, com->VarList[i]);
						strcat(fullcommand, " ");
						i++;
					}
					newjob->command = fullcommand; // stores the values to the new object
					
					newjob->pid = childPid;
					newjob->mode = 0;
					newjob->nextjob = NULL;
					if (head != NULL) { // determines if there are any jobs running
						struct job *tempjob = (struct job*) malloc(sizeof(struct job)); // tempjob for finding size
						for (tempjob = head; tempjob != NULL; tempjob = tempjob->nextjob) {
							numjobs++; // finds the current jobID
						}
						newjob->num = numjobs;
					} else { // sets head and tail to the only job
						newjob->num = 1;
						head = newjob;
						tail = newjob;
						continue;
					}
					
					tail->nextjob = newjob; // sets the old tail's next to the current tail
					tail = newjob; // sets the current tail
					continue;
				} else {
					waitpid(childPid, &status, 0); // TODO -- do I need to store the status?
					if (WIFSIGNALED(status)){
						fprintf(stderr, "Unique Error\n");
					}
				}
			}
		}
		free_info(info);
		free(cmdLine);

	} /* while(1) */
}
