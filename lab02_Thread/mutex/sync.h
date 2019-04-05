//
// Created by jyxk on 19-3-25.
//

#ifndef MUTEX_SYNC_H
#define MUTEX_SYNC_H

#include <sys/types.h>
#include <sys/sem.h>
#include <errno.h>

#define FALSE 0
#define TRUE 1

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
#if defined(__linux__)
    struct seminfo *__buf;
#endif
};

extern int bsUseSemUndo;
extern int bsRetryOnEintr;

int initSemAvailable(int semId, int semNum);
int initSemInUse(int semId, int semNum);
int initSemValue(int semId, int semNUm, int semValue);

int reserveSem(int semId, int semNum);//P operation
int releaseSem(int semId, int semNum);//V operation

#endif //MUTEX_SYNC_H
