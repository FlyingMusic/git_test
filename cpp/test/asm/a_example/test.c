#include <stdio.h>

int main(int argc, char* argv[]) {
#if 0
    int *p = (int*)argc;
    (*p)++;
    __asm__("":::"memory");
    (*p) = 9999;
    __asm__("":::"memory");
    if ((*p) == 9999)
        return 5;
    return *p;
#endif
    printf("add const int to int:\n");
    int c = 2;
    printf("c = %d\n", c);
    __asm__("add $5, %0" : "+m"(c));
    printf("c = %d\n", c);
    
    printf("swap two int:\n");
    int a = 2;
    int b = 3;
    printf("a = %d, b = %d\n", a, b);
    __asm__("xchg %0, %1;" : "+a"(a), "+b"(b));
    printf("a = %d, b = %d\n", a, b);

    printf("if-else:\n");
    //a = b = 8;
    int r = 2;
    __asm__("cmp %%ebx, %%ecx;" \
            "jne .nequal;" \ 
            "mov $1, %%eax;"
            "je .equal;" \ 
            ".nequal: mov $0, %%eax;"
            ".equal: " : "+a"(r): "b"(a), "c"(b));
    printf("a = %d, b = %d, r = %d\n", a, b, r);

    printf("loop:");
    int sum = 0;
    __asm__("mov $100, %%ecx;" \
            ".cmp: cmp $0, %%ecx;" \
            "jne .loop;" \
            "jmp .end;" \
            ".loop: addl %%ecx, %0; dec %%ecx; jmp .cmp;" \
            ".end: ": "=a"(sum));
            
    printf("sum = %d\n", sum);
            

}
