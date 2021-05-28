#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void thread_fun() 
{
    printf("thread...\n");
    sleep(20);
}

int main()
{
    pthread_t pt;
    int ret = pthread_create(&pt, NULL, (void*(*)(void*))thread_fun, NULL);
    if(ret != 0) {
        printf("pthread_create error!\n");
        return -1;
    }
    char pthread_name[16] = {0};
    ret = pthread_getname_np(pt, pthread_name, 16);
    if(ret != 0) {
        printf("pthread_getname_np error!\n");
        return -1;
    }
    printf("old name: %s\n", pthread_name);
    
    pthread_setname_np(pt, "hello pthread");
    if(ret != 0) {
        printf("pthread_setname_np error!\n");
        return -1;
    }
    
    pthread_getname_np(pt, pthread_name, 16);
    if(ret != 0) {
        printf("pthread_getname_np error!\n");
        return -1;
    }
    printf("new name: %s\n", pthread_name);
    pthread_join(pt, NULL);
    
    return 0;
}
