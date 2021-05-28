#include <stdio.h>
#include <string.h>

static bool allZero(const char *number, int lef, int rig);
static bool isDigit(char c);
static void appendCharToStr(char *str, char c);
static bool pureDigit2Chinese(const char *digit, char *chinese);

const char *single_num_to_chn[] = {"零", "一", "二", "三", "四", "五", "六", "七", "八", "九"};
const char *power[] = {"", "十", "百", "千", "万", "十", "百", "千", "亿", "十", "百", "千", "万"};

bool digit2chinese(const char *digit, char *chinese) {
    if(digit == NULL || chinese == NULL) {
        return false;
    }
    char buf[256] = {0};
    char result[256] = {0};
    int len = strlen(digit);
    int buflen = 0;
    for(int i = 0; i < len; ++i) {
        if( !isDigit(digit[i]) ) {
            if(buflen != 0) {
                memset(result, 0, 256);
                pureDigit2Chinese(buf, result);
                memset(buf, 0, 256);
                buflen = 0;
                strcat(chinese, result);
            }
            appendCharToStr(chinese, digit[i]);
        } else {
            buf[buflen++] = digit[i];
            buf[buflen] = '\0';
        }
    }
    if(buflen != 0) {
        pureDigit2Chinese(buf, result);
        strcat(chinese, result);
    }
}


static bool allZero(const char *number, int lef, int rig) {
    for(int i = lef; i < rig; ++i) {
        if(number[i] != '0') {
            return false;
        }
    }
    return true;
}

static bool isDigit(char c) {
    if(c >= '0' && c <= '9') {
        return true;
    } else {
        return false;
    }
}

static void appendCharToStr(char *str, char c) {
    char tmp[2] = {0};
    tmp[0] = c;
    tmp[1] = '\0';
    strcat(str, tmp);
}

static bool pureDigit2Chinese(const char *digit, char *chinese) {
    int len = strlen(digit);
    if(len > 13) {
        strcat(chinese, "out of range");
        return false;
    }
    bool need_zero = false;
    for(int i = 0; i < len; ++i) {
        if(digit[i] == '0') {
            need_zero = true;
            if(len-i-1 == 8) {
                strcat(chinese, power[len-i-1]);
            }
            if(len-i-1 == 4 && (len < 9 || !allZero(digit, i-3, i+1))) {
                strcat(chinese, power[len-i-1]);
            }
            continue;
        }
        if(need_zero) {
            strcat(chinese, "零");
            need_zero = false;
        }
        strcat(chinese, single_num_to_chn[digit[i]-'0']);
        strcat(chinese, power[len-i-1]);
    }
    return true;
}
