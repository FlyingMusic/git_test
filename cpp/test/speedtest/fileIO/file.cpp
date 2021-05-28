#include <stdio.h>
#include <sys/time.h>

int main()
{
    struct timeval start;
    struct timeval end;

    FILE *fp = fopen("test.txt", "a");
    for(int i = 0; i < 1000; ++i) {
        fprintf(fp, "%d\n", i);
    }
    fclose(fp);
    
    int tmp = 0;
    gettimeofday(&start,NULL);
    for(int i = 0; i < 1000; ++i) {
        fp = fopen("test.txt", "r");
        fscanf(fp, "%d", &tmp);
        fclose(fp);
    }
    gettimeofday(&end,NULL);
    double time_use=(end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("time_use is %.10lf us\n",time_use);
}
