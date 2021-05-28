#include <stdio.h> 
#include <string.h> 
#include <cctype> 

bool isAllDigit(const char *text) {
    const char *p = text;
    while(*p != '\0') {
        if(!isdigit(*p) && *p != ' ' && *p != '\n') {
            return false;
        }
        ++p;
    }
    return true;
}

int main() 
{
    FILE *fpR = fopen("123.txt", "r");
    char inputBuff[4] = {0};
    fgets(inputBuff, 4, fpR);
    printf("len = %d\n", strlen(inputBuff));
    if(!isAllDigit(inputBuff)) {
        printf("error\n");
        return -1;
    }
    int a = 0;
    int b = 0;
    int c = 0;
    sscanf(inputBuff, "%d %d %d", &a, &b, &c);
    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);

}
