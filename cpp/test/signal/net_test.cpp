#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
 
#define THREAD_NUM 2
pthread_t tid[10];
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
void sig_handler(int sig)
{
        pthread_mutex_lock(&mutex);
    printf("%ld sig_handler\n", pthread_self());
    sleep(1);
        pthread_mutex_unlock(&mutex);
}
 
void *thread_handler(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("%ld thread_handler\n", pthread_self());
        sleep(1);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

int main()
{
    printf("%ld main_handler\n", pthread_self());
    signal(SIGINT, sig_handler);
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&tid[i], NULL, thread_handler, NULL);
    }
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("%ld main_handler lock\n", pthread_self());
        sleep(1);
        sleep(1);
        sleep(1);
        pthread_mutex_unlock(&mutex);
        printf("%ld main_handler unlock\n", pthread_self());
        sleep(1);
    }

    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
 
    return 0;   
}
