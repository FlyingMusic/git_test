#include <string>
#include <string.h>
#include <stdio.h>

using namespace std;

int main()
{
    FILE *fpI = fopen("./nlu_param.txt", "r+"); 
    if(NULL == fpI) {
        printf("open file fail\n");
        return -1;
    }
    char json[2048] = {0};
    fgets(json, sizeof(json), fpI);
    string str = json;
    printf("%s\n", str.c_str());
    string::size_type pos = str.find("\"text\":\"\"");
    if(pos == s.npos) {
        str.insert(str.find("\"ASR_PARAM\":{"), "\"text\":\"打开天窗\"");
    } else {
        str = str.replace(iter, strlen("\"text\":\"\""), "\"text\":\"打开天窗\"");
    }
    printf("%s\n", str.c_str());
    return 0;
}
