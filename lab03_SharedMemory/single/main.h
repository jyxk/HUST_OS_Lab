//
// Created by jyxk on 19-3-19.
//

#ifndef LAB03_SHAREDMEMORY_MAIN_H
#define LAB03_SHAREDMEMORY_MAIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>

#include "sem.h"

#define OBJ_PERMS (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)

#define AVAILABLE 0
#define FINISH 1

#define EMPTY 0
#define FULL 1
#define MUTEX 2

#define BUF_SIZE 1024
#define BUF_NUM 10

typedef struct RingBuff {
    int status;
    int size;
    int nextShmid;
    char data[BUF_SIZE];
} RingBuff;


int readRing(int read_fd, int tailShmid, int semid);
int writeRing(int write_fd, int headShmid, int semid);

#endif //LAB03_SHAREDMEMORY_MAIN_H
