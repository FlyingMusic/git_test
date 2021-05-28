#include <stdio.h>
#include <string.h>

char *myStrtok(char *str, const char **spltr,const int spltrNum, char **pSave) {
    if((str==NULL && *pSave==NULL) || *pSave!=NULL && **pSave=='\0') { return NULL; }
    for(int i = 0; i < spltrNum; ++i) if(spltr[i]==NULL) { return NULL; }

    char *start = str!=NULL ? str : *pSave;
    char *pSp[spltrNum];
    for(int i = 0; i < spltrNum; ++i) {
        pSp[i] = strstr(start, spltr[i]);
    }
    char *pLef = start+strlen(start);
    int minIndexSp = -1;
    for(int i = 0; i < spltrNum; ++i) {
       if(pSp[i]!=NULL && pLef>pSp[i]) { pLef = pSp[i]; minIndexSp = i; }
    }
    if(minIndexSp == -1) {
        *pSave = pLef;
        return start;
    }
    *pSave = pLef+strlen(spltr[minIndexSp]);
    *pLef = '\0';
    return start;
}
int main()
{
    char text[] = "欢迎使用普强语音助手，为您的出行保驾护航，支撑一片天地。";
    
    char* pSave = NULL;
    const char  *pSpliter[] = {"，", "？", "！", "。"};
    char* value = myStrtok(text, pSpliter, sizeof(pSpliter)/sizeof(pSpliter[0]), &pSave);
    while(value) {
        printf("value = %s\n", value);
        value = myStrtok(NULL, pSpliter, sizeof(pSpliter)/sizeof(pSpliter[0]), &pSave);
    }
    return 0;        
}
