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

class Control {
public:
    void addA(shared_ptr<A> a) {
        aVec.push_back(a);
    }
private:
    vector<shared_ptr<A>> aVec;
};
int main() {
    Control c;
    shared_ptr<A> pa = make_shared<B>();
    c.addA(pa);
    c.addA(pa);
    c.addA(pa);
    c.addA(pa);
    c.addA(pa);
    return 0;
}
