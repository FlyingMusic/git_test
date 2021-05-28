#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

typedef struct file_info_st {
    char d_name [32];
    struct stat buf;
} file_info;
int main()
{
    //FILE *file = fopen("123.txt", "wb");
    //fclose(file);
    DIR *dir;
    struct dirent *ptr;

    if((dir=opendir("./text/")) == NULL) {
        printf("open dir fail...\n");
        return 0;
    }
    file_info filesInfo[10];
    int fileNum = 0;
    while((ptr=readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0) {
            continue;
        }
        snprintf(filesInfo[fileNum].d_name, 32, "./text/%s", ptr->d_name);
        int status = stat(filesInfo[fileNum].d_name, &(filesInfo[fileNum].buf));
        if(status != 0) {
            printf("stat file %s error!!\n", filesInfo[fileNum].d_name);
        }
        fileNum++;
    }
    for(int i = 0; i < fileNum; ++i) {
        printf("%s %d\n", filesInfo[i].d_name, filesInfo[i].buf.st_atime);
    }
    closedir(dir);
    for(int i = fileNum-1; i > 0; --i) {
        for(int j = 0; j < i; ++j) {
            if(filesInfo[j].buf.at_ctime > filesInfo[j+1].buf.st_atime){
                file_info tmp = filesInfo[j];
                filesInfo[j] = filesInfo[j+1];
                filesInfo[j+1] = tmp;
            }
        }
    }
    for(int i = 0; i < fileNum; ++i) {
        printf("%s %d\n", filesInfo[i].d_name, filesInfo[i].buf.st_atime);
    }

    int status = remove(filesInfo[0].d_name);
    if(status != 0) {
        printf("remove file %s error!!\n", filesInfo[0].d_name);
    }
    return 0;     

}
