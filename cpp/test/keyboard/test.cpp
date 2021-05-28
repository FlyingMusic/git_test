#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    char text[5];
    char input[5];
    while(true) {
        sprintf(text,"%d%d%d%d\0", rand()%10, rand()%10, rand()%10, rand()%10);
        printf("%s\n", text);
        gets(input);
        if(0 == strcmp(text, input)) {
            printf("SUCCESS\n");        
        } else {
            printf("FAIL\n");     
        }
    }
}
