//
// Created by jyxk on 19-3-19.
//

#ifndef LAB03_SHAREDMEMORY_MAIN_H
#define LAB03_SHAREDMEMORY_MAIN_H

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "sem.h"

#define SHM_KEY 0x1234
#define SEM_KEY 0x5678

#define OBJ_PERMS (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)

#define WRITE_SEM 0
#define READ_SEM 1

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

struct shmseg {
    int cnt;
    char buf[BUF_SIZE];
};

#endif //LAB03_SHAREDMEMORY_MAIN_H
