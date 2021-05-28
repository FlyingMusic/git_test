#include <stdio.h>

int main()
{
    FILE *fp = fopen("digit_cmn.model", "rb");
    if(fp == NULL) {
        printf("open file fail!!!\n");
        return -1;
    }
    char text[512];
    int line = 0;
    while(fgets(text, 512, fp)) {
        ++line;
    }
    printf("line = %d\n", line);
    return 0;
}
