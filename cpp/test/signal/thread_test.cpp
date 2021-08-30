#include <stdio.h>
#include <thread>
#include <pthread.h>
#include <mutex>
#include <signal.h>
#include <unistd.h>
 
#define THREAD_NUM 10

using namespace std;

static std::recursive_mutex g_mutex;

void sig_handler(int sig)
{
    // while (1)
    {
        std::unique_lock<std::mutex> lock(g_mutex);
        printf("sig lock\n");
        sleep(1);
        printf("sig unlock\n");
    }
}
 
void *thread_handler(void *arg)
{
    while (1)
    {
        {
            std::unique_lock<std::mutex> lock(g_mutex);
            printf("thread1 lock\n");
            sleep(1);
            printf("thread1 unlock\n");
        }
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
    signal(SIGINT, sig_handler);
    pthread_t tid[1];
    int i;
    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(&tid[i], NULL, thread_handler, NULL);
    }
    pthread_t t;
   // pthread_create(&t, NULL, t_handler, NULL);
 
    for (i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(tid[i], NULL);
    }
 
    return 0;   
}
