#include <stdio.h>

int main()
{
    FILE *fpW = fopen("text.txt", "w");
    fprintf(fpW, "%d %d %d\n", 1, 2, 3);
    fprintf(fpW, "%d %d %d\n", 4, 5, 6);
    fprintf(fpW, "%d %d %d\n", 7, 8, 9);
    fclose(fpW);

    FILE *fpM = fopen("text.txt", "r+");
    fseek(fpM, 6, SEEK_SET);
    fprintf(fpM, "%c", 'x');
    fclose(fpM);
    return 0;
}
