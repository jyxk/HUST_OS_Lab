//
// Created by jyxk on 19-4-15.
//

#include <stdio.h>
#include "sem.h"
#include "main.h"

int main(int argc, char *argv[]) {

    if (argc != 4) {
        printf("Arg error!\n");
        exit(-1);
    }

    printf("%s %s %s %s\n", argv[0], argv[1], argv[2], argv[3]);

    int readFd = open(argv[1], O_RDONLY);
    if (readFd == -1) {
        printf("Read file error!\n");
        exit(-1);
    }

    int buffHeadId = strtol(argv[2], NULL, 10);
    int semid = strtol(argv[3], NULL, 10);
    printf("%d %d\n", buffHeadId, semid);

    readRing(readFd, buffHeadId, semid);
    return 0;
}

int readRing(int readFd, int tailShmid, int semid) {

    int readNum;
    RingBuff * tail = (RingBuff *)shmat(tailShmid, NULL, 0);
    if (tail == (void *)-1) {
        printf("read buffer shared memory attach error!\n");
        exit(-1);
    }
    while (1) {
        reserveSem(semid, FULL);
        reserveSem(semid, MUTEX);

        readNum = read(readFd, tail->data, BUF_SIZE);
        if (readNum == -1) {
            printf("read file error!");
            exit(-1);
        }

        if (readNum < BUF_SIZE) {
            tail->status = FINISH;
            tail->size = readNum;
            close(readFd);
            releaseSem(semid, MUTEX);
            releaseSem(semid, EMPTY);
            return 0;
        }

        tail->size = BUF_SIZE;
        tailShmid = tail->nextShmid;
        tail = (RingBuff *)shmat(tailShmid, NULL, 0);

        if (tail == (void *)-1) {
            printf("read buffer shared memory attach error!\n");
            exit(-1);
        }
        releaseSem(semid, MUTEX);
        releaseSem(semid, EMPTY);
    }
}