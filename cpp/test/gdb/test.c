#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>    

int main()
{
//    int a = 0;
//    scanf("%d", &a);
//   int arr[a];
    char a[4] = {0};
    strncpy(a, "RIFF", sizeof(4));
    printf("%s\n", a);
    return 0;
}
