#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getFileCoding(const char* path);
bool isPrintText(const char* str,int length);
bool isUTF8Text(const char* pBuffer, int length);
bool isGBKText(const char* str,int length);
  
int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("please input: Filename\n");
		printf("egs:%s digitnormal.txt\n", argv[0]);
		return -1;
    }
	getFileCoding(argv[1]);
	printf("\n");
}

int getFileCoding(const char* path) {
    if(NULL == path) {
        printf("path is NULL!!");
        return 0;
    }
    
    FILE *fp = fopen(path, "rb"); 
   
    if (NULL == fp) {  
       return 0;  
    }  
   
    char text[512] = {0};
	while(!feof(fp)){
	    memset(text, 0, sizeof(text));
        fgets(text, sizeof(text) - 1, fp);
        int len = strlen(text);
		if('\r' == text[len - 1] || '\n' == text[len - 1]){
            text[len - 1] = '\0';
        }
		len = strlen(text);
		printf("%s %d\n", text, len);
		printf("isPrintText:%d\n", isPrintText(text, len));
		printf("isUTF8Text:%d\n", isUTF8Text(text, len));
		printf("isGBKText:%d\n", isGBKText(text, len));
		if(isPrintText(text, len)) {
			continue;
		}
		if(isUTF8Text(text, len) && !isGBKText(text, len)) {
			printf("UTF8\n");
			return 0;
		}
		if(isGBKText(text, len) && !isUTF8Text(text, len)) {
			printf("GBK\n");
			return 0;
		}	
	}
	printf("UNKNOWN\n");
	return 0;
	/*
    fseek(fp, 0, SEEK_END);  
    long lSize = ftell(fp);  
    fseek(fp, 0, SEEK_SET);
   
    char *pBuff = new char[lSize + 1];  
    memset(pBuff, 0, lSize + 1);  
    fread(pBuff, lSize, 1, fp);  
    fclose(fp);  
   
    bool isUTF8 = IsUtf8(pBuff, lSize);  
    delete []pBuff;  
    pBuff = NULL;  
   
    return isUTF8==true ? 0 : 1;  
	*/
}
bool isPrintText(const char* str,int length)
{
	int i = 0;
	while(i < length) {
		if(!(isprint(str[i]) || str[i]=='\t')) {
			return false;
		}
		++i;
	}
	return true;
}

 bool isGBKText(const char* str,int length){
	int i = 0;
	while(i + 1 < length) {
		if(isprint(str[i]) || str[i]=='\t') {
			++i;
			continue;
		}
		if( !((unsigned char)str[i]>=0x81 && (unsigned char)str[i]<=0xfe && (unsigned char)str[i+1]>=0x40 && (unsigned char)str[i+1]<=0xfe) ) {
			return false;			
		}
		i += 2;
	}
    return true;
}
 bool isUTF8Text( const char* str,int length ){
    int i;
    //UFT8可用1-6个字节编码,ASCII用一个字节
    int nBytes=0;
    unsigned char chr;

    for(i=0;i<length;i++)
    {
        chr= *(str+i);
        //如果不是ASCII码,应该是多字节符,计算字节数
        if(nBytes==0)
        {
            if(chr>=0x80)
            {
                if(chr>=0xFC&&chr<=0xFD)
                {
                    nBytes=6;
                }
                else if(chr>=0xF8)
                {
                    nBytes=5;
                }
                else if(chr>=0xF0)
                {
                    nBytes=4;
                }
                else if(chr>=0xE0)
                {
                    nBytes=3;
                }
                else if(chr>=0xC0)
                {
                    nBytes=2;
                }
                else
                {
                    return false;
                }
                nBytes--;
            }
        }
        //多字节符的非首字节,应为 10xxxxxx
        else
        {
            if( (chr&0xC0) != 0x80 )
            {
                return false; 
            }
            nBytes--;
        }
    }
    //违返规则
    if( nBytes > 0 )
    {
        return false;
    }
    return true;
}
