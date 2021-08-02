#include <stdio.h>

int main() {
    const int constant = 21;
    int* modifier = (int*)(&constant);
    *modifier = 99;
    printf("constant = %d\n", constant);
    printf("*modifier = %d\n", *modifier);
    printf("&constant = 0x%x\n", &constant);
    printf("modifier = 0x%x\n", modifier);
    return 0;
}
