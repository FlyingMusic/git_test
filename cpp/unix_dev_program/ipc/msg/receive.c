#include <stdio.h>
#include <errno.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>

#define MSG_KEY_FILE "./msg.key"
#define PRJ_ID 0x1

struct msg_st {
    long int msg_type;
    char text[BUFSIZ];
};

void thread_fun1(void *arg) {
    printf("thread1...\n");

    long int msgid = *(long int*)arg;
    struct msg_st data;

    // 从队列中获取消息，直到遇到end消息为止
    while (1) {
        long int msgtype = 1;   // 注意1
        if (msgrcv(msgid, (void *)&data, BUFSIZ, msgtype, 0) == -1) {
            printf("thread1 msgrcv failed\n");
        }
        printf("thread1 receive: %s\n", data.text);

        // 遇到end结束
        if (strncmp(data.text, "end", 3) == 0) {
            break;
        }
    }

}

void thread_fun2(void *arg) {
    printf("thread2...\n");

    long int msgid = *(long int*)arg;
    struct msg_st data;

    // 从队列中获取消息，直到遇到end消息为止
    while (1) {
        long int msgtype = 2;   // 注意2
        if (msgrcv(msgid, (void *)&data, BUFSIZ, msgtype, 0) == -1) {
            printf("thread2 msgrcv failed\n");
        }
        printf("thread2 receive: %s\n", data.text);

        // 遇到end结束
        if (strncmp(data.text, "end", 3) == 0) {
            break;
        }
    }

}

int main(int argc, char **argv) {
    int msgid = -1;

    //获取key
    key_t key = ftok(MSG_KEY_FILE, PRJ_ID);
    if (-1 == key) {
        printf("ftok failed, errno[%d]\n", errno);
        return -1;
    }
    // 建立消息队列
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (-1 == msgid) {
        printf("msgget failed\n");
        return -1;
    }
    printf("msgid = %d\n", msgid);

    //开启两个线程，分别处理两种消息
    pthread_t pt[2];
    int ret = pthread_create(&pt[0], NULL, (void*(*)(void*))thread_fun1, &msgid);
    if(ret != 0) {
        printf("pthread_create error!\n");
        return -1;
    }

    ret = pthread_create(&pt[1], NULL, (void*(*)(void*))thread_fun2, &msgid);
    if(ret != 0) {
        printf("pthread_create error!\n");
        return -1;
    }

    pthread_join(pt[0], NULL);
    pthread_join(pt[1], NULL);

    // 删除消息队列
    if (msgctl(msgid, IPC_RMID, 0) == -1) {
        printf("msgctl error!\n");
        return -1;
    }
    return 0;
}
