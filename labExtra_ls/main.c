#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 1024

void ListFile(const char *name, int depth);
void depthTab(int depth);
int main(int argc, char const *argv[]) {

    const char *file_path = argv[1];
    const char *target_file[argc];

    for (int i = 2; i < argc; i++) 
        target_file[i-2] = argv[i];
    
    if ((file_path == NULL) || (target_file == NULL)) {
        printf("Wrong Input!\n");
        exit(-1);
    }

    ListFile(file_path, 0);

	return 0;
}

struct stat statbuf;
struct tm *timeinfo;
void ListFile(const char *name, int depth) {
    DIR *dir;
    struct dirent *entry;

    char timeBuf[MAX_LENGTH] = {};
    if (!(dir = opendir(name)))
        exit(-1);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            char path[MAX_LENGTH];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            depthTab(depth);
            stat(path, &statbuf);
            timeinfo = localtime(&statbuf.st_mtim);
            strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %H:%M:%S", timeinfo);
            printf("[uid:%d gid:%d size:%luBYTE(s) Modified time:%s] %s\n", statbuf.st_uid, statbuf.st_gid, statbuf.st_size, timeBuf, path);
            ListFile(path, depth+1);
        } 
        else {
            char absolute_path[MAX_LENGTH];
            sprintf(absolute_path, "%s/%s", name, entry->d_name);
            depthTab(depth);
            stat(absolute_path, &statbuf);
            timeinfo = localtime(&statbuf.st_mtim);
            strftime(timeBuf, sizeof(timeBuf), "%Y/%m/%d %H:%M:%S", timeinfo);
            printf("[uid:%d gid:%d size:%luBYTE(s) Modified time:%s] %s\n", statbuf.st_uid, statbuf.st_gid, statbuf.st_size, timeBuf, absolute_path);

        }
    }
    closedir(dir);
}

void depthTab(int depth) {
    for (int i = 0; i < depth; i++)
        putchar('\t');
}