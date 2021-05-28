#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RecordUserData.h"

int getContent(const char *filename, char *content) {
    struct stat statbuf;
    if (stat(filename, &statbuf) == -1) {
        printf("stat file[%s] error\n", filename);
        return -1;
    }
    int filesize = statbuf.st_size;
    FILE *fpR = fopen(filename, "r");
    if (NULL == fpR) {
        printf("fopen fail\n");
        return -1;
    }
    if(fread(content, sizeof(char), filesize, fpR) != (size_t)filesize) {
        printf("fread fail\n"); 
        fclose(fpR);
        return -1;
    }
    fclose(fpR);
    return 0;
}

int main() {

    char content[2048] = {0};
    RecordUserData rud;
    memset(content, 0, sizeof(content));
    getContent("phone.json", content);
    rud.setUserData(content);
 
   
    memset(content, 0, sizeof(content));
    getContent("phone_history.json", content);
    rud.setUserData(content);
 
    memset(content, 0, sizeof(content));
    getContent("phone.json", content);
    rud.setUserData(content);

   
    memset(content, 0, sizeof(content));
    getContent("music.json", content);
    rud.setUserData(content);
   
   /* 
    memset(content, 0, sizeof(content));
    getContent("sum.json", content);
    rud.setUserData(content);
    
    */
    printf("%s\n", rud.getUserData());
    
    return 0;
}


