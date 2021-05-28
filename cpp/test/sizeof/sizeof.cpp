#include <stdio.h>
class A{
        public:
virtual ~A(){}
short int ttt;
};

int main()
{
    printf("%d\n", sizeof(int*));
    printf("%d\n", sizeof(int));
    printf("%d\n", sizeof(short int));
    A a;

    printf("%d\n", sizeof(A));
    printf("%d\n", sizeof(a));
    return 0;
}
