#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
 
#define THREAD_NUM 10

static pthread_mutex_t mutex;
static pthread_mutexattr_t attr;
 
void sig_handler(int sig)
{
    // while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("sig lock\n");
        sleep(1);
        printf("sig unlock\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
 
void *thread_handler(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        printf("thread1 lock\n");
        sleep(1);
        sleep(1);
        printf("thread1 unlock\n");
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}
void *t_handler(void *arg)
{
    while (1)
    {
        printf("thread2 lock\n");
        sleep(1);
        printf("thread2 unlock\n");
        sleep(1);
    }
}
int main()
{
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
    //pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&mutex, &attr);
    signal(SIGINT, sig_handler);
    pthread_t tid[1];
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&tid[i], NULL, thread_handler, NULL);
    }
    pthread_t t;
  //  pthread_create(&t, NULL, t_handler, NULL);
 
    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
 
    return 0;   
}
