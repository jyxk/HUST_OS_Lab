//
// Created by jyxk on 19-3-17.
//
#include "sync.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define COMPUTE 0
#define PRINT 1

int sum = 0;

int semId;

void* compute(void *arg) {
    for (int i = 1; i <= 100; i++) {

        if (reserveSem(semId, COMPUTE) == -1) {//P operation
            printf("P operation for compute error!\n");
            exit(-1);
        }

        sum += i;

        if (releaseSem(semId, PRINT) == -1) {
            printf("V operation for print error!\n");
            exit(-1);
        }
    }

    return NULL;
}

void* print(void *arg) {
    for (int i = 1; i <= 100; i++) {
        if (reserveSem(semId, PRINT) == -1) {
            printf("P operation for print error!\n");
            exit(-1);
        }

        printf("The sum is %d\n", sum);

        if (releaseSem(semId, COMPUTE) == -1) {
            printf("V operation for compute error!\n");
            exit(-1);
        }
    }

    return NULL;
}

int main(void) {
    pthread_t pthread[2];
    void *threadResult;

    //创造信号量
    if ((semId = semget(IPC_PRIVATE, 2, S_IRUSR | S_IWUSR)) == -1) {
        printf("Get semaphore error!\n");
        exit(-1);
    }
    if (initSemAvailable(semId, COMPUTE) == -1) {
        printf("Inital semaphore for compute error!\n");
        exit(-1);
    }
    if (initSemInUse(semId, PRINT) == -1) {
        printf("Inital semaphore for print error!\n");
        exit(-1);
    }

    //线程
    if (pthread_create(&pthread[0], NULL, compute, NULL) != 0) {
        printf("Create thread compute error!\n");
        exit(-1);
    }

    if (pthread_create(&pthread[1], NULL, print, NULL) != 0) {
        printf("Create thread print error!\n");
        exit(-1);
    }

    //pthread_join(pthread[0], &threadResult);
    pthread_join(pthread[1], &threadResult);
    if (semctl(semId, IPC_RMID, 0) == -1) {
        printf("Delete sem error!\n");
        exit(-1);
    }

    return 0;

}