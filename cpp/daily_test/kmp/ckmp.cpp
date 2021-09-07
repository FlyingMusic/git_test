#include <stdio.h>
#include <string.h>

void getLast(const char *pattern, int *last) {
    int plen = strlen(pattern);
    last[0] = -1;
    int i = 0;
    int start = -1;
    while (i < plen - 1) {
        if (start == -1 || pattern[i] == pattern[start]) { 
            last[++i] = ++start;
        } else { //不相等时，需要将start变小
            start = last[start]; //x处失配，则从last[x]处重新匹配
        }
    }
}
const char *myStrStr(const char *str, const char *pattern) {
    if (!str || !pattern) {
        printf("param is invalid!\n");
        return NULL;
    }
    const int slen = strlen(str);
    const int plen = strlen(pattern);
    int last[plen];
    getLast(pattern, last);
    for (int i = 0; i < plen; ++i) {
        printf("%d ", last[i]);
    }
    printf("\n");
    int sidx = 0;
    int pidx = 0;
    while (pidx < plen && sidx < slen) {
        if (pidx == -1 || str[sidx] == pattern[pidx]) {
            sidx++;
            pidx++;
        } else {
            pidx = last[pidx]; 
        }
    }
    if (pidx == plen) {
        return str + sidx - plen;
    }
    return NULL;
}
int main() {
    const char *str =  "abcabcabdddabcabcxyz";
    const char *pattern = "aacabdddabcabcx";
    //const char *pattern = "abcabcabcabcabc";
    //const char *pattern = "aaaaaaa";
    const char *p = myStrStr(str, pattern);
    if (p)
        printf("%s\n", p);
    else
        printf("no match\n");
    return 0;
}
