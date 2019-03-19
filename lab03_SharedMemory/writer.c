//
// Created by jyxk on 19-3-19.
//
#include <stdio.h>
#include "shm.h"
#include "sem.h"

int main(int argc, char *argv[]) {
    int semid, shmid, bytes, xfrs;
    struct shmseg *shmp;
    union semun dummy;

    semid = semget(SEM_KEY, 2, IPC_CREAT | OBJ_PERMS);
    if (semid == -1) {
        printf("semget error!\n");
        exit(-1);
    }
    if (initSemAvailable(semid, WRITE_SEM) == -1) {
        printf("initSemAvailable error!\n");
        exit(-1);
    }
    if (initSemInUse(semid, READ_SEM) == -1) {
        printf("initSemInUse error!\n");
        exit(-1);
    }

    shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | OBJ_PERMS);
    if (shmid == -1) {
        printf("shmget error!\n");
        exit(-1);
    }

    shmp = shmat(shmid, NULL, 0);
    if (shmp == (void *) -1) {
        printf("shmat error!\n");
        exit(-1);
    }

    for (xfrs = 0, bytes = 0; xfrs++, bytes += shmp->cnt) {
        if (reserveSem(semid, WRITE_SEM) == -1) {
            printf("reserveSem error!\n");
            exit(-1);
        }
    }

    shmp->cnt = read(STDIN_FILENO, shmp->buf, BUF_SIZE);
    if (shmp->cnt == -1) {
        printf("read error!\n");
        exit(-1);
    }

    if (releaseSem(semid, READ_SEM) == -1) {
        printf("releaseSem error!\n");
        exit(-1);
    }

    if (shmp->cnt == 0)
        break;

    if (reserveSem(semid, WRITE_SEM) == -1) {

    }
}