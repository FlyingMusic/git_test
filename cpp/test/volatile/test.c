#include <stdio.h>

int main() {
    volatile int a = 0;    
    a++;
    a++;
    a++;
    a++;
    printf("a = %d\n", a);
}
