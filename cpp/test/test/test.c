#include <stdio.h>

int main() {
    char *p = malloc(128);
    printf("p = 0x%x\n", p);
    p = malloc(512 * 1024);
    printf("p = 0x%x\n", p);
    return 0;
}
