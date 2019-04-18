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

    int writeFd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, OBJ_PERMS);
    //printf("WriteFd %d", writeFd);
    if (writeFd == -1) {
        printf("Write file error!\n");
        exit(-1);
    }

    int buffHeadId = strtol(argv[2], NULL, 10);
    int semid = strtol(argv[3], NULL, 10);
    printf("%d %d\n", buffHeadId, semid);
    writeRing(writeFd, buffHeadId, semid);
    return 0;
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

        //if (head->status == FINISH) {
        if (head->size < BUF_SIZE) {
            write(writeFd, head->data, head->size);

            close(writeFd);
            releaseSem(semid, MUTEX);
            releaseSem(semid, FULL);
            return 0;
        }
        write(writeFd, head->data, BUF_SIZE);

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