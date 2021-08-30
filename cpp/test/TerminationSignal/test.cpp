#include <stdio.h>
#include <unistd.h>


int main() {
    for (int i = 0; i < 1000; i++) {
        int a =  *(int*)NULL;
        printf("%s\n", NULL);
        printf("i = %d\n", i);
        sleep(1);
    }
    return 0;
}
