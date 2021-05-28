#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

bool isResourceExist(const char *resPath) {
    DIR *dir;
    struct dirent *ptr;

    if(resPath == NULL) { return false; }

    if((dir=opendir(resPath)) == NULL) {
        printf("open %s fail!!!\n", resPath); return false;
    }
    
    while((ptr=readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0) {
            continue;
        }
        if(ptr->d_type == 4) { //dir
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    return false;
}
int main()
{
    if(isResourceExist("./text/")) {
        printf("resource exist!!!\n");
    } else {
        printf("no resource!!!\n");
    }
    return 0;
}
