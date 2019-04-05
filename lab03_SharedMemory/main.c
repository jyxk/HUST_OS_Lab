//
// Created by jyxk on 19-3-19.
//
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <wait.h>

#include "main.h"
#include "sem.h"

int semid;

int main(int argc, char *argv[]) {

    int readFd, writeFd;
    int buffHeadId;
    int tmp;
    pid_t readId, writeId;

    if (argc != 3) {
        printf("arg error! \nUsage:./cp <src> <dst>\n");
        exit(-1);
    }
    //Open files
    readFd = open(argv[1], O_RDONLY);
    writeFd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, OBJ_PERMS);

    if ((semid = semget(IPC_PRIVATE, 3, S_IRUSR|S_IWUSR)) == -1) {
        printf("Get semephore error!\n");
        exit(-1);
    }

    if (initSemInUse(semid, EMPTY) == -1) {
        printf("Init empty error!");
        exit(-1);
    }

    if (initSemValue(semid, FULL, BUF_NUM) == -1) {
        printf("Init FULL error!\n");
        exit(-1);
    }

    if (initSemAvailable(semid, MUTEX) == -1) {
        printf("Init mutex error!\n");
        exit(-1);
    }

    /*
     * 利用shmid作为环形缓存指针,创建缓存
     */

    if ((buffHeadId = shmget(IPC_PRIVATE, sizeof(RingBuff), IPC_CREAT|OBJ_PERMS)) == -1) {
        printf("Shared memory get error!\n");
        exit(-1);
    }
    RingBuff *ringTmp = (RingBuff*)shmat(buffHeadId, NULL, 0);
    if (ringTmp == (void *) -1) {
        printf("Attach error!\n");
        exit(-1);
    }

    for (int i = 0; i < BUF_NUM; i++) {
        int newShmId;
        if ((newShmId = shmget(IPC_PRIVATE, sizeof(RingBuff), IPC_CREAT | OBJ_PERMS)) == -1) {
            printf("Shared memory get error!\n");
            exit(-1);
        }
        ringTmp->nextShmid = newShmId;
        ringTmp->status = AVAILABLE;
        ringTmp = (RingBuff *)shmat(newShmId, NULL, 0);
        if (ringTmp == (void *) -1) {
            printf("Attach error!\n");
            exit(-1);
        }
        ringTmp->nextShmid = buffHeadId;

        readId = fork();
        if (readId == -1) {
            printf("read fork error!\n");
            exit(-1);
        }
        else if (readId == 0) {
            readRing(readFd, buffHeadId, semid);
            exit(0);
        }
        else {
            writeId = fork();
            if (writeId == -1) {
                printf("write fork error!\n");
                exit(-1);
            }
            else if (writeId == 0) {
                writeRing(writeFd, buffHeadId, semid);
                exit(0);
            }
            else {
                waitpid(readId, &tmp, 0);
                waitpid(writeId, &tmp, 0);
                if (semctl(semid, 0, IPC_RMID, 0) == -1) {
                    printf("Remove semaphore error!\n");
                    exit(-1);
                }
                exit(0);
            }
        }

    }
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

        if (readNum == 0) {
            tail->status = FINISH;
            tail->size = readNum;
            close(readFd);
            releaseSem(semid, MUTEX);
            releaseSem(semid, EMPTY);
            return 0;
        }

        tail->size = readNum;
        tailShmid = tail->nextShmid;
        tail = (RingBuff *)shmat(tailShmid, NULL, 0);

        if (tail == (void *)-1);
        releaseSem(semid, MUTEX);
        releaseSem(semid, EMPTY);
    }
}

int writeRing(int writeFd, int headShmid, int semid) {
    RingBuff *head = (RingBuff *)shmat(headShmid, NULL, 0);

    if (head == (void *)-1) {
        printf("write buffer shared memory attach error!\n");
        exit(-1);
    }

    while (1) {
        reserveSem(semid, EMPTY);
        reserveSem(semid, MUTEX);

        if (head->status == FINISH) {
            write(writeFd, head->data, head->size);
            close(writeFd);
            releaseSem(semid, MUTEX);
            releaseSem(semid, FULL);
            return 0;
        }
        write(writeFd, head->data, head->size);
        headShmid = head->nextShmid;
        head = shmat(headShmid, NULL, 0);
        if (head == (void *)-1) {
            printf("write buffer shared memory attach error!\n");
            exit(-1);
        }
        releaseSem(semid, MUTEX);
        releaseSem(semid, FULL);

    }

}