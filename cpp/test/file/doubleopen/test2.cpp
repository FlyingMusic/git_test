#include <stdio.h>
#include <unistd.h>

int main()
{
    FILE *pf = fopen("123.txt", "ab");
    if (pf == NULL) {
        printf("open file error!!!\n");
    }
    const char *pText = "abcdefghijklmn";
    int cnt = 0;
    while(cnt < 5) {
        fwrite(pText+cnt, sizeof(char), 1, pf);
        cnt++;
        sleep(1);
        printf("%d\n", cnt);
    }
    fclose(pf);
    return 0;
}
