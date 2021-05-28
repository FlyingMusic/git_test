#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("./text.txt", O_RDWR|O_CREAT|O_EXCL, 0777);
    if(fd == -1) {
        printf("open text.txt fail!!!\n");
        return -1;
    }
    write(fd, (const void*)"abcdef", sizeof("abcefe"));
    return 0;
}
