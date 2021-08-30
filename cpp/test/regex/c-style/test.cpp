#include <regex.h>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

bool ttsRegMatch(const char *pattern, const char *text)
{
#if 1 
    string str_p = pattern;
    int pos = -1;
    pos = str_p.find("(");
    if(pos != -1)
        str_p = str_p.replace(pos, 1 ,"\\(");
    pos = str_p.find(")");
    if(pos != -1)
        str_p = str_p.replace(pos, 1 ,"\\)");
    pos = str_p.find("[");
    if(pos != -1)
        str_p = str_p.replace(pos, 1 ,"\\)");
    pos = str_p.find("]");
    if(pos != -1)
        str_p = str_p.replace(pos, 1 ,"\\)");
    pos = str_p.find("?");
    if(pos != -1)
        str_p = str_p.replace(pos, 1 ,"\\?");
    pattern = str_p.c_str();
#endif
    printf("%s\n", pattern);
    printf("%s\n", text);
 
    regex_t reg;
    int ret = regcomp(&reg, pattern, REG_EXTENDED);
    if(0 != ret) {
        printf("regcomp error, ret[%d]\n", ret);
        return false;
    }
   const size_t nmatch = 1;
    regmatch_t pmatch[1];
    int status = regexec(&reg, text, nmatch, pmatch, 0);

    if (status == REG_NOMATCH){
        return false;
    } else if (status == 0){
        if(pmatch[0].rm_eo - pmatch[0].rm_so == strlen(text)) {
            regfree(&reg);
            return true;
        } else {
            regfree(&reg);
            return false;
        }
    }
    regfree(&reg);
    return 0;
}
int main()
{
    printf("%d\n", ttsRegMatch("Ther.e are 4 applications, which one to open.", "Ther.e are 4 applications, which one to open."));
    return 0;
}
