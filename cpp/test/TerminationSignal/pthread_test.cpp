#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void thread_porcess(void *obj){ 
    int i = *(int*)obj;
    while (true) {
        sleep(1);
        printf("i = %d\n", i);
    }
}

int main() {
    int thread_num = 10;
    pthread_t pids[thread_num];
    for(int i = 0; i < thread_num; i++){
        if(pthread_create(pids+i, NULL, (void*(*)(void*))&thread_porcess, &i) != 0){
            printf("create pthread[%d] failed!\n", i);
        } else {
            printf("create pthread[%d] succeed!\n", i);
            pthread_detach(pids[i]); 
        }
        usleep(200*1000);
    }
    sleep(100);
    return 0;
}
