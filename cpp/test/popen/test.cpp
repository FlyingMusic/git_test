#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = popen("cat abc.txt", "r");
    if (!fp) {
        printf("popen failed!!!\n"); 
        return -1;
    }
    char buff[1024] = {0};
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        if (strstr(buff, "Sum")) {
            break;
        }
    }
    const char *split = "\t\r\n ";
    char *key, *value, *p;
    key = strtok_r(buff, split, &p);
    if(key == NULL){
        return -1;
    }
    printf("%s\n", key);
    while (true) {
        key = strtok_r(NULL, split, &p);
        if(key == NULL){
            return -1;
        }
        printf("%s\n", key);
    }

    return 0;
}
