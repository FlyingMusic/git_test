#include <stdio.h>
#include <stdlib.h>

int main() {
    char *p = (char *)malloc(1);
    for (int i = -10; i < 30; ++i) {
        printf("%d 0x%hhx\n", i, p[i]);
    }
    free(p);
    return 0;
}
