#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE_NAME "./file.fifo"

int main() {
    if ((mkfifo(FIFO_FILE_NAME, 0666) < 0) && (errno != EEXIST)) {
        printf("create fifo file[%s] failed!!\n", FIFO_FILE_NAME);
        return -1;
    } else {
        printf("create fifo file[%s] succeed!!\n", FIFO_FILE_NAME);
    }

    int fd = open(FIFO_FILE_NAME, O_RDONLY | O_NONBLOCK); //no block
    if(fd < 0) {
        printf("open fifo file[%s] failed!!\n", FIFO_FILE_NAME);
        return -1;
    } else {
        printf("open fifo file[%s] succeed!!\n", FIFO_FILE_NAME);
    }
    while (1) {
        int fifo_data = 0;
        int read_bytes = read(fd, &fifo_data, sizeof(fifo_data));
        if(read_bytes <= 0) {
            if(EAGAIN == errno || 0 == errno) {
                sleep(1);
                continue;
            }
            printf("read fd[%d] failed, errno[%d]!!\n", fd, errno);
            close(fd);
            break;
        }
        printf("read data[%d] from fifo\n", fifo_data);
    }
    unlink(FIFO_FILE_NAME);
}
