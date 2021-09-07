#include <stdio.h>
#include <string.h>

void getLast(const char *pattern, int *last) {
    int plen = strlen(pattern);
    last[0] = 0;
    int i = 1;
    int start = 0;
    while (i < plen) {
        if (pattern[i] == pattern[start]) { //i+1失配时，填入i处的值，所以i处的值是跟前面相等的下一个，即start++
            start++;
            last[i++] = start;
        } else { //不相等时，需要将start变小
            if (start == 0) { //已经变小到0
                last[i++] = 0;
            } else {
                start = last[start-1]; //x处失配，则从last[x-1]处重新匹配
            }
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
        if (str[sidx] == pattern[pidx]) {
            sidx++;
            pidx++;
        } else {
            if (pidx == 0) {
                sidx++;
            } else {
                pidx = last[pidx-1]; 
            }
        }
    }
    if (pidx == plen) {
        return str + sidx - plen;
    }
    return NULL;
}
int main() {
    const char *str =  "abcabcabdddabcabcxyz";
    const char *pattern = "abcabdddabcabcx";
    //const char *pattern = "abcabcabcabcabc";
    //const char *pattern = "aaaaaaa";
    const char *p = myStrStr(str, pattern);
    if (p)
        printf("%s\n", p);
    else
        printf("no match\n");
    return 0;
}
