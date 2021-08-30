#include <stdio.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
 
#define THREAD_NUM 10

pthread_t tid[10];
 

int sum = 0;

void *thread_handler(void *arg)
{
    for (int i = 0; i < 1000; ++i)
    {
        usleep(100);
        sum++;
    }
}

int main()
{
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&tid[i], NULL, thread_handler, NULL);
    }

    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
 
    printf("sum = %d\n", sum);
    return 0;   
}
