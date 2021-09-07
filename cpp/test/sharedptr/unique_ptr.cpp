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

class Control  {
public:
    Control(unique_ptr<A> upa) {
        m_upa = std::move(upa);
    }
private:
    unique_ptr<A> m_upa;
};
int main() {
    unique_ptr<A> upa(new B());
    Control c(std::move(upa));

    unique_ptr<A> p3(new A());

    return 0;
}
