#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void thread_fun() 
{
    printf("thread...\n");
    sleep(2);
}

int main()
{
    pthread_t pt;
    int ret = pthread_create(&pt, NULL, (void*(*)(void*))thread_fun, NULL);
    if(ret != 0) {
        printf("pthread_create error!\n");
        return -1;
    }
    pthread_join(pt, NULL);
    
    return 0;
}
