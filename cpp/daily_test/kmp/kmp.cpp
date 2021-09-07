#include <stdio.h>
#include <string.h>

void getLast(const char *pattern, int *last) {
    int plen = strlen(pattern);
    last[0] = 0;
    int i = 1;
    int start = 0;
    while (i < plen) {
        if (pattern[i] == pattern[start]) { //i+1失配时，填入i处的值，所以i处的值是跟前面相等的下一个，即start++
            //这个地方填的一定是++start,因为i和start处是匹配的，所以以后匹配的时候，当i失配后，不可能再从start比较
            //一定是从start+1处开始比较，至于这个值放到哪儿，可以灵活处置，可以放到i处，也可以放到i+1处
            //放到i出似乎比较合理，但i处这个值表示的是当i+1失配后，要跳的值，也就是后面的x = last[x-1]，即当前位置失配
            //后，要跳转的地方放在前一个位置
            //放到i+1处，则正好左移了一位，下标跟失配位置匹配上了，即x = last[x],即当前位置失配后，要跳转的前面的位置就
            //放在当前位置
            //0-start是前缀 i是后缀结尾
            last[i++] = ++start;
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
