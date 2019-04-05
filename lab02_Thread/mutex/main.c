#include "sync.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MUTEX 0


int ticketSum = 100000;
int counterSH = 0;
int counterWH = 0;
int semId;

void* shanghai(void *arg) {

    while (1) {
        //sleep(1);
        if (reserveSem(semId, MUTEX) == -1) {
            printf("P shanghai error!\n");
            exit(-1);
        }

        if (ticketSum > 0) {
            printf("上海卖出一张票,剩余: %d 张\n", --ticketSum);
            counterSH++;
        }
        else {
            printf("上海票售净!售出%d张\n", counterSH);
            releaseSem(semId, MUTEX);
            break;
        }

        if (releaseSem(semId, MUTEX) == -1) {
            printf("V wuhan error!\n");
            exit(-1);
        }

    }
    return NULL;
}

void* wuhan(void *arg) {
    while (1) {
        if (reserveSem(semId, MUTEX) == -1) {
            printf("P wuhan error!\n");
            exit(-1);
        }

        if (ticketSum > 0) {
            printf("武汉卖出一张票,剩余: %d 张\n", --ticketSum);
            counterWH++;
        }
        else {
            printf("武汉票售净!售出%d张\n", counterWH);
            releaseSem(semId, MUTEX);
            break;
        }

        if (releaseSem(semId, MUTEX) == -1) {
            printf("V shanghai error!\n");
            exit(-1);
        }

    }
    return NULL;
}

int main() {
    pthread_t pthread[2];
    void *threadResult;


    if ((semId = semget(IPC_PRIVATE, 1, S_IRUSR | S_IWUSR)) == -1) {
        printf("Get semaphore error!\n");
        exit(1);
    }
    if (initSemAvailable(semId, MUTEX) == -1) {
        printf("Inital semaphore available error!\n");
        exit(-1);
    }

    if (pthread_create(&pthread[0], NULL, shanghai, NULL) != 0) {
        printf("Create thread shanghai error!\n");
        exit(-1);
    }

    if (pthread_create(&pthread[1], NULL, wuhan, NULL) != 0) {
        printf("Create thread wuhan error!\n");
        exit(-1);
    }

    pthread_join(pthread[0], &threadResult);
    pthread_join(pthread[1], &threadResult);

    if (semctl(semId, IPC_RMID, 0) == -1) {
        printf("Delete sem error!\n");
        exit(-1);
    }

    return 0;
}