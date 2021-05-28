#include <stdio.h>
#include <sys/stat.h>

int main()
{
    struct stat statbuf;
    if(stat("./text.txt", &statbuf) != -1){
        printf("size = %u\n", statbuf.st_size);
    }    
    return 0;
}
