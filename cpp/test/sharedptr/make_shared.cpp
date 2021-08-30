#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class A {
public:
    A() { cout << "A()" << endl; }
    virtual ~A() { cout << "~A()" << endl; }
};

class B : public A{
public:
    B() { cout << "B()" << endl; }
    virtual ~B() { cout << "~B()" << endl; }
};

int main() {
    shared_ptr<A> pa1(new B());
    shared_ptr<A> pa2 = make_shared<B>();
    return 0;
}
