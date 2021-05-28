#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    struct timeval start_tv;
    struct timeval end_tv;

    gettimeofday(&start_tv,NULL); 
    sleep(10);
    gettimeofday(&end_tv,NULL);
    
    double time_use=(end_tv.tv_sec-start_tv.tv_sec)*1000000+(end_tv.tv_usec-start_tv.tv_usec);//微秒
    printf("time_use is %.10f\n", time_use);
    printf("%u\n", start_tv.tv_sec);
    printf("%u\n", end_tv.tv_sec);
}
