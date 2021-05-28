#include <stdio.h>

static bool isAllDigit(const char *text) {
    while(text != NULL && *text != '\0') {
        if(!(*text >= '0' && *text <= '9')) {
            return false;
        }
        ++text;
    }
    return true;
}
int main(){
    printf("%d\n", isAllDigit("12345a"));
    return 0;
}

test
12
test
12
12
test
53
test
test
2323
test
