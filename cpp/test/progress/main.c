#include <stdlib.h>  
#include <stdio.h>  
#include "process.h"  
     
#define MAX_PID_NUM     32  
int main(int argc, char* argv[])  
{  
  char* process;  
  int ret = 0;  
  int n;  
  pid_t pid[MAX_PID_NUM];  
      
  if(argc < 2)  
    process = argv[0];  
  else  
    process = argv[1];  
      
  ret = get_pid_by_name(process, pid, MAX_PID_NUM);  
  printf("process '%s' is existed? (%d): %c\n", process, ret, (ret > 0)?'y':'n');  
  for(n=0;n<ret;n++){  
    printf("%u\n", pid[n]);  
  }  
  return ret;  
}
