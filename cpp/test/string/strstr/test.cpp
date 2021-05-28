#include <stdio.h>
#include <string.h>

static char *publicNumber = "10086-10010-10000-110-114-119-120";

bool isMatch(const char *text) {
    int slotsLen = strlen(text);
    char tmpChar[32];
    bzero(tmpChar, sizeof(tmpChar));
    snprintf(tmpChar, sizeof(tmpChar), "%s", text);
    if(strstr(publicNumber, tmpChar) != NULL) {
        return true;
    } else {
        return false; 
    }
}

int main()
{
    if(isMatch("11")) {
        printf("%s\n", "110");
    }
    return 0;
}
