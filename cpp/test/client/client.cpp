#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include "msg_type.h"

int send_request(int fd);
int recv_responce(int fd);
int send_data(int fd);
int send_finish(int fd);
int recv_result(int fd);

void thread_porcess(void *arg) 
{
//    while(true) {
        int socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if(socket < 0) {
            printf("socket fd[%d] is invalid!\n");
            return;
        }
        printf("pthreadid[%d]: socket[%d] success...\n", pthread_self(), socketfd);

        int port = 5555;
        char ip[] = "192.168.128.70";
        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_aton(ip, &server_addr.sin_addr);
        int ret = connect(socketfd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
        if(ret < 0) {
            printf("pthreadid[%u]: connect error[%s]\n", pthread_self(), strerror(errno));
            close(socketfd);
            return;
        }
        printf("pthreadid[%u]: connect success!\n", pthread_self());
        if(send_request(socketfd) != 0) {
            printf("pthreadid[%u]: send request fail\n", pthread_self());
            close(socketfd);
            return;
        }
        if(recv_responce(socketfd) != 0) {
            printf("pthreadid[%u]: recv responce fail\n", pthread_self());
            close(socketfd);
            return;
        }
        if(send_data(socketfd) != 0) {
            printf("pthradid[%u]: send data fail\n", pthread_self());
            close(socketfd);
            return;
        }
        if(send_finish(socketfd) != 0) {
            printf("pthreadid[%u]: send finish fail\n", pthread_self());
            close(socketfd);
            return;
        }
        if(recv_result(socketfd) != 0) {
            printf("pthreadid[%u]: recv finish fial\n", pthread_self());
            close(socketfd);
            return;
        }
        close(socketfd);
 //   }
    return;
}
int send_request(int fd)
{
    msg_head_st head;
    head.cmd = CMD_REQUEST;
    head.datalen = 0;
    int sendlen = send(fd, &(head), sizeof(head), MSG_DONTWAIT);
    if(sendlen != sizeof(head)) {
        printf("pthreadid[%u]: send request error[%s]\n", pthread_self(), strerror(errno));
        return -1;
    }
    printf("pthreadid[%u]: send request success\n", pthread_self());
    return 0;
}
int recv_responce(int fd) 
{
    msg_head_st head;
    int recvret = recv(fd, &(head), sizeof(head), MSG_WAITALL);
    if(recvret < 0) {
        printf("pthreadid[%u]: recv error[%s]\n", pthread_self(), strerror(errno));
        return -1;
    }
    if(recvret == 0) {
        printf("pthreadid[%u]: server close the connection\n", pthread_self());
        return -1;
    }
    if(head.cmd != CMD_RESPONCE) {
        printf("pthreadid[%u]: recv responce error\n", pthread_self());
        return -1;
    }
    printf("pthreadid[%u]: recv responce success\n", pthread_self());
    return 0;
}
int sum_send = 0;
int send_data(int fd) 
{
    FILE *fpR = fopen("./client", "rb");
    if(fpR == NULL) {
        printf("open file error\n");
        return -1;
    }
    char sendbuff[1024] = {0};
    msg_head_st head;
    head.cmd = CMD_DATA;
    int bytes = 0;
    while((bytes = fread(sendbuff+sizeof(head), 1, 500, fpR)) != 0) {
        head.datalen = bytes;
        memcpy(sendbuff, &head, sizeof(head));
        int sendlen = send(fd, sendbuff, sizeof(head)+head.datalen, MSG_WAITALL);
        if(sendlen != sizeof(head)+head.datalen) {
            printf("pthreadid[%u]: send error[%s]\n", pthread_self(), strerror(errno));
            return -1;
        }
        sum_send += bytes;
        printf("pthreadid[%u]: send sum data[%d] success\n", pthread_self(), sum_send);
    }
    printf("pthreadid[%u]: send data finish\n", pthread_self());
    fclose(fpR);
    return 0;
}
int send_finish(int fd)
{
    msg_head_st head;
    head.cmd = CMD_FINISH;
    head.datalen = 0;
    int sendlen = send(fd, &(head), sizeof(head), MSG_DONTWAIT);
    if(sendlen != sizeof(head)) {
        printf("pthreadid[%u]: send finish error[%s]\n", pthread_self(), strerror(errno));
        return -1;
    }
    printf("pthreadid[%u]: send finish success\n", pthread_self());
    return 0;
}
int recv_result(int fd)
{
    char recvbuff[1024] = {0};
    int recvret = recv(fd, recvbuff, sizeof(msg_head_st)+32, MSG_WAITALL);
    if(recvret < 0) {
        printf("pthreadid[%u]: recv error[%s]\n", pthread_self(), strerror(errno));
        return -1;
    }
    if(recvret == 0) {
        printf("pthreadid[%u]: server close the connection\n", pthread_self());
        return -1;
    }

    msg_head_st head;
    memcpy(&head, recvbuff, sizeof(head));
    if(head.cmd != CMD_RESULT) {
        printf("pthreadid[%u]: recv responce error\n", pthread_self());
        return -1;
    }
    char result[64] = {0};
    memcpy(result, recvbuff+sizeof(head), 32);
    result[33] = '\0';
    printf("pthreadid[%u]: recv result[%s] success\n", pthread_self(), result);
    return 0;
}
#define N 1
int main()
{
    pthread_t pid[N];
    for(int i = 0; i < N; i++) {
        int pret = pthread_create(&pid[i],NULL,(void*(*)(void*))&thread_porcess,NULL);
        if(pret != 0){
            printf("pthread[%d] create fail!!!", i);
            return -1;
        }
    }
    for(int i = 0; i < N; i++) {
        pthread_join(pid[i], NULL);
    }
    return 0;
}
