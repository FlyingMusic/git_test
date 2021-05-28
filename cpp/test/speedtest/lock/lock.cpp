#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <mutex> //锁库

static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;

using namespace std;
 
std::mutex g_mutex;

int main()
{
    struct timeval start;
    struct timeval end;

    int sum = 0;
    gettimeofday(&start,NULL);
    for(int i = 0; i < 100000; ++i) {
        std::unique_lock<std::mutex> lock( g_mutex );        
        sum += i;
    }
    gettimeofday(&end,NULL);
    double time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("time_use is %.10lf us\n",time_use);
    return 0;
}
