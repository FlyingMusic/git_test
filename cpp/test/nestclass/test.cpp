#include <stdio.h>

class A {
public:
    A(){ printf("A\n"); }
    ~A(){ printf("~A\n"); }
    class B {
    public:
        B(){ printf("B\n");} 
        ~B(){ printf("~B\n");} 
    };
};

int main()
{
    A a;
}
