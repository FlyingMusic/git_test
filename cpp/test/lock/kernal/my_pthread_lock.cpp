#include <stdio.h>
#include <pthread.h>
#include <linux/futex.h>
#include <syscall.h>
#include <unistd.h>
#include <sys/time.h>
 
 
#define NUM 1000
 
 
int num = 0;
int futex_addr = 0;
 
int futex_wait(void* addr, int val){
    return syscall(SYS_futex, addr, FUTEX_WAIT, val, NULL, NULL, 0);
}
int futex_wake(void* addr, int val){
  return syscall(SYS_futex, addr, FUTEX_WAKE, val, NULL, NULL, 0);
}
 
void* thread_f(void* par){
    int id = (long long) par;

    /*go to sleep*/
    for(int i = 0; i < 1000; ++i){
        while(1 == __sync_val_compare_and_swap(&futex_addr, 0, 1) ){
            futex_wait(&futex_addr,1);
        }
        ++num;
        futex_addr = 0;
        futex_wake(&futex_addr, NUM);
    }
    //printf("Thread %d starting to work!\n",id);
    return NULL;
}

int main(){
    pthread_t threads[NUM];
    int i;

    printf("Everyone go...\n");
    float time_use=0;
    struct timeval start;
    struct timeval end;
    gettimeofday(&start,NULL);



    for (i=0;i<NUM;i++){
        pthread_create(&threads[i],NULL,thread_f,(void *)i);
    }

    /*wake threads*/

    /*give the threads time to complete their tasks*/
    for (i=0;i<NUM;i++){
        pthread_join(*(threads + i), NULL);
    }


    printf("Main is quitting...\n");
    printf("and num is %d\n", num);
 
    gettimeofday(&end,NULL);
    time_use=(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec) / 1000000.0;//微秒
    printf("time_use is %f \n",time_use);
    return 0;
}
