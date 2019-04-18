#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1024

typedef struct folderNode {
    char *path;
    struct folderNode *next;
} FolderNode;

void ListFile(const char *name);
void depthTab(int depth);

int depth = 0;

int main(int argc, char const *argv[]) {

    const char *file_path = argv[1];
    const char *target_file[argc];

    for (int i = 2; i < argc; i++)
        target_file[i-2] = argv[i];

    if ((file_path == NULL) || (target_file == NULL)) {
        printf("Wrong Input!\n");
        exit(-1);
    }

    ListFile(file_path);

    return 0;
}


void ListFile(const char *name) {
    DIR *dir;
    struct dirent *ptr;
    struct stat statbuf;
    struct tm *timeinfo;
    char *filename;
    char *filepath;
    char *data;
    char *foldername;
    char *folderpath;

    FolderNode folderStart;
    folderStart.path = name;
    folderStart.next = NULL;

    FolderNode *folderFirst = &folderStart;
    FolderNode *folderLast = &folderStart;

    char timeBuf[MAX_LENGTH] = {};

    while (folderFirst != NULL) {
        dir = opendir(folderFirst->path);
        if (dir) {
            while ((ptr = readdir(dir)) != NULL) {
                if (ptr->d_type == DT_DIR) {
                    if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
                        continue;

                    char path[MAX_LENGTH] = {};
                    sprintf(path, "%s/%s", folderFirst->path, ptr->d_name);
                    depthTab(depth);
                    stat(path, &statbuf);
                    timeinfo = localtime(&statbuf.st_mtim);
                    strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %H:%M:%S", timeinfo);
                    printf("[uid:%d gid:%d size:%luBYTE(s) Modified time:%s] %s\n", statbuf.st_uid, statbuf.st_gid, statbuf.st_size, timeBuf, path);

                    FolderNode *folderNew = malloc(sizeof(FolderNode));
                    folderNew->path = malloc(strlen(path) +1);
                    strcpy(folderNew->path, path);
                    folderNew->next = NULL;

                    folderLast->next = folderNew;
                    folderLast = folderNew;
                    depth ++;
                }
                else {
                    char absolute_path[MAX_LENGTH] = {};
                    sprintf(absolute_path, "%s/%s", folderFirst->path, ptr->d_name);
                    depthTab(depth);
                    stat(absolute_path, &statbuf);
                    timeinfo = localtime(&statbuf.st_mtim);
                    strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %H:%M:%S", timeinfo);
                    printf("[uid:%d gid:%d size:%luBYTE(s) Modified time:%s] %s\n", statbuf.st_uid, statbuf.st_gid, statbuf.st_size, timeBuf, absolute_path);

                }
            }
        }
        else
            return ;

        folderFirst = folderFirst->next;
        closedir(dir);
    }

}

void depthTab(int depth) {
    for (int i = 0; i < depth; i++)
        putchar('\t');
}