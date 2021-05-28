#include <stdio.h>
#include <ctype.h>

void strToLower(const char *src, char *dst, int size) {
    if(src == NULL || dst == NULL) {
        return;
    }
    if(strlen(src) > size) {
        return; //防止传入的串过长，导致内存越界
    }
    while(1) {
        *dst = tolower(*src);
        if(*src == '\0') {
            break;
        }
        ++dst;
        ++src;
    }
}

int main() {
    char src[128] = "A1B2CdEFG";
    char dst[128] = "xxxxxxxxxxxxxxxxxxxxx";
    strToLower(src, dst, sizeof(src));
    printf("%s\n", dst);
    return 0;
}

