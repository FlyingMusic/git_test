#include <pthread>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void write_func(int fd) {
    
}
int main() {
    int fd = open("123.txt", O_RDWR);
    if(-1 == fd) {
        printf("open file error!\n");
        return -1;
    }
    int ret = pthread_create();
}
