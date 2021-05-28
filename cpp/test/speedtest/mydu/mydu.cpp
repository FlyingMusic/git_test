#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/stat.h>

unsigned int  getCacheFileSize(const char *path) {

    DIR *dir = NULL;
    struct dirent *ptr = NULL;

    if((dir=opendir(path)) == NULL) {
        printf("getCacheFileSize: opedir fail\n");
        return 0;
    }

    unsigned int sum_size = 0;
    while((ptr=readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0) {
            continue;
        }

        char tmpChar[128] = {0};
        snprintf(tmpChar, 128, "%s%s", path, ptr->d_name);
        struct stat statbuf;
        int status = stat(tmpChar, &statbuf);
        if(status != 0) {
            printf("getCacheFileSize: stat file %s error!!\n", tmpChar);
            continue;
        }
        sum_size += statbuf.st_size;
    }
    closedir(dir);
    return sum_size;
}

int main()
{
    struct timeval start;
    struct timeval end;

    gettimeofday(&start,NULL);
    printf("size = %u\n", getCacheFileSize("./recordings/"));
    gettimeofday(&end,NULL);
    double time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("time_use is %.10lf us\n",time_use);
    return 0;
}
