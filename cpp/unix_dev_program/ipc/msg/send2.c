#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/msg.h>
#include <errno.h>
 

#define MSG_KEY_FILE "./msg.key"
#define PRJ_ID 0x1

struct msg_st {
    long int msg_type;
    char text[BUFSIZ];
};

int main(int argc, char **argv)
{
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
 
    struct msg_st data;
    // 向消息队里中写消息，直到写入end
    while (1) {
        printf("Enter some text: \n");
        fgets(data.text, BUFSIZ, stdin);
        data.msg_type = 2; // 注意2
        
        // 向队列里发送数据
        if (msgsnd(msgid, (void *)&data, BUFSIZ, 0) == -1) {
            printf("msgsnd failed\n");
            return -1;
        }
 
        // 输入end结束输入
        if (strncmp(data.text, "end", 3) == 0) {
            break;
        }
    }
    return 0; 
}
