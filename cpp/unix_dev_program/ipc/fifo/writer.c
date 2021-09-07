#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE_NAME "./file.fifo"

int main() {
    //写端要注意，如果不想因为管道异常而退出程序，需要屏蔽SIGPIPE信号
    struct sigaction sigact;
    memset(&sigact, 0, sizeof(struct sigaction));
    sigact.sa_handler = SIG_IGN;
    sigact.sa_flags = 0;
    sigact.sa_restorer = NULL;
    sigaction(SIGPIPE, &sigact, NULL);

    int fd = open(FIFO_FILE_NAME, O_WRONLY|O_NONBLOCK);
    if(fd < 0) {
        printf("open fifo file[%s] failed, errno[%d]\n", FIFO_FILE_NAME, errno);
        return -1;
    }
    int i = 0;
    for(; i < 10; ++i) {
        int write_bytes = write(fd, &i, sizeof(i));
        if(write_bytes <= 0) {
            if(errno == EWOULDBLOCK || errno == EAGAIN) {
                printf("write fifo[%s] failed, fifo is full\n", FIFO_FILE_NAME);
            } else {
                printf("write fifo[%s] failed, errno[%d]\n", FIFO_FILE_NAME, errno);
                close(fd);
                fd = -1;
                return -1;
            }
        } else {
            printf("write data[%d] to fifo[%s] succeed\n", i, FIFO_FILE_NAME);
        }
        sleep(2);
    }
}
