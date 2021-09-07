#include <stdio.h>
#in

class A {
public:
    int m_a;
    A() { printf("A()\n"); }
    ~A() { printf("~A()\n"); }
    A(const A& other) { 
        printf("A(const A& other)\n");
    }
    A(const A&& other) { 
        printf("A(const A& other)\n");
    }
    A& operator=(const A& other) { 
        printf("A& operator=(const A& other)\n");
        return *this;
    }
};

A&& getTemp()
{
    A a;
    a.m_a = 9;
    printf("%d\n", a.m_a);
    return std::move(a);
}

int main() {
    A a = getTemp();   //getTemp()的返回值是右值（临时变量）
    a.m_a = 1;
    printf("%d\n", a.m_a);
    return 0;
}

