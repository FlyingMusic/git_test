#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[])
{
    int pid;
    /* fork another process */
    pid = fork();
    if (pid<0) // pid都是大于等于0的
    { 
            /* error occurred */
            fprintf(stderr,"Fork Failed!");
            exit(-1);
    } 
    else if (pid==0) // 子进程的返回值（eax寄存器保存）是0，所以子进程进入else if条件分支
    {
            /*  child process   */
            execlp("/home/chenyifei/code/github/git_test/cpp/test/strace/test","test",NULL);// 在子进程中加载指定的可执行文件
    } 
    else  // 父进程的返回值（eax寄存器保存）> 0，所以父进程进入else条件分之
    { 
            /*    parent process  */
            /* parent will wait for the child to complete*/
            wait(NULL);
            printf("Child Complete!\n");
            exit(0);
    }
    return 0;
}
 
 
 
 
 
