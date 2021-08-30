#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval start;
    struct timeval end;

    gettimeofday(&start,NULL); 
    long long sum = 0;
    int i = 0;
    for (i = 0; i < 10000000; ++i) {
        sum += i;
    }
    gettimeofday(&end,NULL);
    printf("sum = %lld\n", sum);
    float time_use=(end.tv_sec-start.tv_sec)*1000000 + (end.tv_usec-start.tv_usec);//微秒
    printf("time_use is %.10f ms\n",time_use/1000.0);

}
