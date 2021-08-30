#include <iostream>

using namespace std;

class A {
    int a;
};
A *pa = NULL;
int main()
{
    pa = new A;
	return 0;
}
