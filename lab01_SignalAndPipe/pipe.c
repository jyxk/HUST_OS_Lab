#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int pipe_fd[2];
pid_t firstChild, secondChild;

void sigusrHandler(int sig);
void sigintHandler(int sig);

int main(void) {
    int countSend = 1, countReceive;

    signal(SIGINT, sigintHandler);

    if (pipe(pipe_fd) == -1) {
        printf("Error: Can't create the pipe!");
        exit(-1);
    }

    firstChild = fork();

    if (firstChild == -1) {
        printf("Error: Failed to create the first child process\n");
        exit(-1);
    }
    else if (firstChild == 0) {
        signal(SIGINT, SIG_IGN);
        signal(SIGUSR1, sigusrHandler);
        while (1) {
            if (write(pipe_fd[1], &countSend, sizeof(int)) != sizeof(int)) {
                printf("Child 1 write error!\n");
                exit(-1);
            }
            countSend++;
            sleep(1);
        }
    }
    else if (firstChild > 0) {
        secondChild = fork();
        if (secondChild == -1) {
            printf("Error: Failed to create the second child process\n");
            exit(-1);
        }
        else if (secondChild == 0) {
            signal(SIGINT, SIG_IGN);
            signal(SIGUSR2, sigusrHandler);

            while (1) {
                int readFlag = read(pipe_fd[0], &countReceive, sizeof(int));
                if (readFlag == -1) {
                    printf("Child 2 read error!\n");
                    exit(-1);
                }
                else if (readFlag == 0) {
                    continue;
                }
                else {
                    printf("Child 1 send Child 2 %d time(s)!\n", countReceive);
                }
            }
        }
        else {
            if (close(pipe_fd[0]) == -1) {
                printf("Parent closed pipe_fd[0] Error!\n");
                exit(-1);
            }
            if (close(pipe_fd[1]) == -1) {
                printf("Parent closed pipe_fd[1] error!\n");
                exit(-1);
            }
            int childStatus;
            waitpid(firstChild, &childStatus, 0);
            waitpid(secondChild, &childStatus, 0);
            printf("Parent Process is Killed!\n");
            exit(0);
        }
    }

}

void sigintHandler(int sig) {
    printf("kill children!");
    kill(firstChild, SIGUSR1);
    kill(secondChild, SIGUSR2);
}

void sigusrHandler(int sig) {
    if (sig == SIGUSR1) {
        printf("The first child is killed by its parent!\n");
        exit(0);
    }
    else if (sig == SIGUSR2) {
        printf("The second child is killed by its parent!\n");
        exit(0);
    }
}