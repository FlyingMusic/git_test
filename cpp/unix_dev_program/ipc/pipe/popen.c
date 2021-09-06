#include <stdio.h>

#define MAXLINE 1024
#define PAGER "${PAGER:-more}"

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    FILE *fpin, *fpout;

    if (argc < 2) {
        printf("usage: %s \"ls -l\"\n", argv[0]);
        return -1;
    }
    if ((fpin = popen(argv[1], "r")) == NULL) {
        printf("can't open %s\n", argv[1]);
    }
    if ((fpout = popen(PAGER, "w")) == NULL) {
        printf("popen error\n");
    }
    while (fgets(line, MAXLINE, fpin) != NULL) {
        if (fputs(line, fpout) == EOF) {
            printf("fputs error to pipe");
        }
    }
    if (ferror(fpin)) {
        printf("fgets error\n");
    }
    if (pclose(fpin) == -1) {
        printf("pclose error\n");
    }
    if (pclose(fpout) == -1) {
        printf("pclose error\n");
    }
    return 0;
}
