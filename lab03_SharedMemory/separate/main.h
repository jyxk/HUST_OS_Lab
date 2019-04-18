//
// Created by jyxk on 19-4-9.
//

#ifndef SEPARATE_MAIN_H
#define SEPARATE_MAIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>

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


void Fatal(const char *msg);
int readRing(int, int, int);
int writeRing(int, int, int);
#endif //SEPARATE_MAIN_H
