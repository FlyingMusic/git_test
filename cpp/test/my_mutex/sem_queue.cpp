#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int sum = 0;

void *thr_consumer(void *arg){
    for(int i = 0; i < 100; ++i) {
        sum = sum + 2;
        usleep(10000);
    }
    return NULL;
}
int main (int argc, char *argv[]){
    int consumer_num = 50;
    pthread_t ctid[consumer_num];
    int ret, i;

    for (i = 0; i < consumer_num; i++) {
        ret = pthread_create(&ctid[i], NULL, thr_consumer, NULL);
        if (ret != 0) {
            return -1;
        }
    }
    for (i = 0; i < consumer_num; i++) {
        pthread_join(ctid[i], NULL);
    }
    printf("sum = %d\n", sum);
    return 0;
}

