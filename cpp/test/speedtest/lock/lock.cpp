#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <mutex> //锁库
#include <atomic> //锁库

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

using namespace std;
 
std::mutex g_mutex;

int main()
{
    struct timeval start;
    struct timeval end;

    int sum = 0;
    double time_use = 0.0;

    gettimeofday(&start,NULL);
    for(int i = 0; i < 100000; ++i) {
        sum += i;
    }
    gettimeofday(&end,NULL);
    time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("origin time_use is %.10lf us\n",time_use);

    sum = 0;
    time_use = 0.0;
    gettimeofday(&start,NULL);
    for(int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&g_lock);
        sum += i;
        pthread_mutex_unlock(&g_lock);
    }
    gettimeofday(&end,NULL);
    time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("c mutex time_use is %.10lf us\n",time_use);

    sum = 0;
    time_use = 0.0;
    std::atomic<int> atomic_sum(0);
    gettimeofday(&start,NULL);
    for(int i = 0; i < 100000; ++i) {
        atomic_sum += i;
    }
    gettimeofday(&end,NULL);
    time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("atomic time_use is %.10lf us\n",time_use);
    

    sum = 0;
    time_use = 0.0;
    gettimeofday(&start,NULL);
    for(int i = 0; i < 100000; ++i) {
        std::unique_lock<std::mutex> lock( g_mutex );        
        sum += i;
    }
    gettimeofday(&end,NULL);
    time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("cpp mutex time_use is %.10lf us\n",time_use);

    return 0;
}
