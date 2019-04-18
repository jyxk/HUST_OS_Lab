#include "main.h"



int main(int argc, char *argv[]) {

    int semid;
    int buffHeadId;
    int tmp;
    //char * src, *dst;
    pid_t readId, writeId;

    if (argc != 3) {
        printf("arg error! \nUsage:./cp <src> <dst>\n");
        exit(-1);
    }

    if ((semid = semget(IPC_PRIVATE, 3, S_IRUSR|S_IWUSR)) == -1)
        Fatal("Semephore");
    if (initSemInUse(semid, EMPTY) == -1)
        Fatal("Init empty error!");
    if (initSemAvailable(semid, MUTEX) == -1)
        Fatal("Init mutex error!");
    if (initSemValue(semid, FULL, BUF_NUM) == -1)
        Fatal("Init FULL error!");

    if ((buffHeadId = shmget(IPC_PRIVATE, sizeof(RingBuff), IPC_CREAT|OBJ_PERMS)) == -1) {
        printf("Shared memory get error!\n");
        exit(-1);
    }
    RingBuff *ringTmp = (RingBuff*)shmat(buffHeadId, NULL, 0);
    if (ringTmp == (void *) -1) {
        printf("Attach error!\n");
        exit(-1);
    }

    char *buffId = malloc(sizeof(char)*20);
    char *StrSemId = malloc(sizeof(char)*20);
    sprintf(buffId, "%d", buffHeadId);
    sprintf(StrSemId, "%d", semid);
    for (int i = 0; i < BUF_NUM; i++) {
        int newShmId;
        if ((newShmId = shmget(IPC_PRIVATE, sizeof(RingBuff), IPC_CREAT | OBJ_PERMS)) == -1) {
            printf("Shared memory get error!\n");
            exit(-1);
        }
        ringTmp->nextShmid = newShmId;
        ringTmp->status = AVAILABLE;
        ringTmp = (RingBuff *) shmat(newShmId, NULL, 0);
        if (ringTmp == (void *) -1) {
            printf("Attach error!\n");
            exit(-1);
        }
    }
        ringTmp->nextShmid = buffHeadId;

        readId = fork();
        if (readId == -1) {
            printf("read fork error!\n");
            exit(-1);
        }
        else if (readId == 0) {
            execl("./reader", "./reader", argv[1], buffId, StrSemId, NULL);
            exit(0);
        }
        else {
            writeId = fork();
            if (writeId == -1) {
                printf("write fork error!\n");
                exit(-1);
            }
            else if (writeId == 0) {
                execl("./writer", "./writer", argv[2], buffId, StrSemId, NULL);
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

void Fatal(const char *msg) {
    perror(msg);
    exit(-1);
}