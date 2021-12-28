#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include<sys/wait.h>

int x;

void handler(int signal) {
    if (x == 0) {
        printf("Got my PARENT's signal of %d my PID = %d, parents' PID = %d\n", signal, getpid(), getppid());
    } else {
        printf("Got my CHILD's signal of %d my PID = %d, child's PID = %d\n", signal, getpid(), x);

    }
}


int main (int argc, char *argv[]) {
    int time;
    int target;
    if (argc == 3) {
        time = atoi(argv[1]);
        target = atoi(argv[2]);
    } else {
        time = 10;
        target = 20;
    }

    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);
    signal(SIGTERM, handler);


    printf("Child sleeps for 10 seconds.\n");

    x = fork();
    if (x == 0) {
        kill(getppid(), SIGUSR2);
        int i;
        //Getting signal from parent right before target completion. Try sending a spearate signal to parent.
        for (i = 1; i < time + 1; i++) {
            int temp = (double) i/time * 100;
            sleep(1);
            printf("Child PID %d @ %d seconds %d%% complete\n", getpid(), i, temp);
        }
        exit(0);
    }
    pause();
    kill(x, SIGUSR1);
    kill(x, SIGTERM);
    int i;
    for (i = 1; i < time + 1; i++) {
        int temp = (double) i / time * 100;
        if (temp >= target) {
            break;
        }
        sleep(1);
    }
    kill(x, SIGUSR2);
    wait(NULL);
    printf("The children have been harvested.\n");

    return 0;


}
