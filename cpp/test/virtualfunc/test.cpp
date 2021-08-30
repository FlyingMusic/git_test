#include <iostream>

using namespace std;

class Base {
public:
    Base() { cout << "Base" << endl; }
    virtual ~Base() { cout << "~Base" << endl; }
};

class Son : public Base {
public:
    Son() { cout << "Son" << endl; }
    ~Son() { cout << "~Son" << endl; }
};

int main() {
    Base *p = new Son;
    delete p;
    return 0;
}
