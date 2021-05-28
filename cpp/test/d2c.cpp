#include <stdio.h>
#include <string.h>
#include "digitToChinese.h"

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("please input test case file!!!\n");
        printf("egs: %s number.txt\n", argv[0]);
        return -1;
    }
    FILE *fpR = fopen(argv[1], "r");
    if( fpR == NULL ) {
        printf("open %s error!!!\n", argv[1]);
        return -1;
    }
    char input[256] = {0};
    char result[256] = {0};
    while(fgets(input, 256, fpR)) {
        memset(result, 0, 256);
        input[strlen(input)-1] = '\0';
        printf("%s\t", input);
        digit2chinese(input, result);
        printf("%s\n", result);
    }
    fclose(fpR);
    return 0;
}




#if 0
void reverse(char *str, char *result) {
    if(strlen(str) == 0) { return; }
    char tmp[4] = {0};
    strncpy(tmp, str, 3);
    tmp[4] = '\0';
    reverse(str+3, result);
    strcat(result, tmp);
}

void convertWithoutWan(const char *lef, const char *rig, char *result) {
    int len = rig - lef;
    for(const char *p = lef; p != rig; ++p) {
        strcat(result, single_num_to_chn[*p - '0']);
        if(*p == '0') { strcat(result, "零"); }
    }
}

#endif
