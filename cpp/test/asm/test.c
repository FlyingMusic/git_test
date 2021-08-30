#include <stdio.h>

int swap(int *lef, int *rig) {
    __asm__("lock xchg %0, %1;"
        : "+r"(*lef), "+r"(*rig)
        :: "memory");
}
int main() {
    int a = 4;
    int b = 5;
    printf("a = %d, b = %d\n", a, b);
    swap(&a, &b);
    printf("a = %d, b = %d\n", a, b);
}
