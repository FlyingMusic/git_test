#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool IsUTF8File(const char* pFileName);
bool IsUTF8Text(const char* pBuffer, long size);
  
int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("please input: Filename\n");
		printf("egs:%s digitnormal.txt\n", argv[0]);
		return -1;
    }
	if(IsUTF8File(argv[1])) {
		printf("UTF_8\n");
	} else {
		printf("GBK\n");
	}
	printf("\n");
}
bool IsUTF8File(const char* pFileName)  
 {  
     FILE *f = fopen(pFileName, "rb"); 
     
     if (NULL == f)  
     {  
         return false;  
     }  
   
     fseek(f, 0, SEEK_END);  
     long lSize = ftell(f);  
     fseek(f, 0, SEEK_SET);  //或rewind(f);  
   
     char *pBuff = new char[lSize + 1];  
     memset(pBuff, 0, lSize + 1);  
     fread(pBuff, lSize, 1, f);  
     fclose(f);  
   
     bool bIsUTF8 = IsUTF8Text(pBuff, lSize);  
     delete []pBuff;  
     pBuff = NULL;  
   
     return bIsUTF8;  
 } 
 
 bool IsUTF8Text( const char* str,long length ){
    int i;
    //UFT8可用1-6个字节编码,ASCII用一个字节
    int nBytes=0;
    unsigned char chr;
    //如果全部都是ASCII, 说明不是UTF-8
    bool bAllAscii= true;
    for(i=0;i<length;i++)
    {
        chr= *(str+i);
        // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个
        // 字节存,最高位标记为0,o0xxxxxxx
        if( (chr&0x80) != 0 )
        {
            bAllAscii= false;
        }
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
    //如果全部都是ASCII, 也是字符串
    if( bAllAscii )
    {
        return true;
    }
    return true;
}
