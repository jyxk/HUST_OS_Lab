#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define FIFO "fifo"

pid_t firstChild, secondChild;

void sigusrHandler(int sig);
void sigintHandler(int sig);

int main(void) {
    int readFd, writeFd;
    
    int countSend = 1, countReceive;

    signal(SIGINT, sigintHandler);

    if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) {
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

        if ((writeFd = open(FIFO, O_WRONLY)) == -1) {
            printf("FIFO writter open error!\n");
            exit(-1);
        }

        while (1) {
            if (write(writeFd, &countSend, sizeof(int)) != sizeof(int)) {
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

            if ((readFd = open(FIFO, O_RDONLY)) == -1) {
                printf("FIFO reader open error!\n");
                exit(-1);
            }

            while (1) {
                int readFlag = read(readFd, &countReceive, sizeof(int));
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
           /* if (close(writeFd) == -1) {
                printf("Parent closed writeFd Error!\n");
                exit(-1);
            }
            if (close(readFd) == -1) {
                printf("Parent closed readFd error!\n");
                exit(-1);
            }*/
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