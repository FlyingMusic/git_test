#include <iostream>
#include <vector>
#include <map>

using namespace std;

class BListener {
public:
    virtual ~BListener() {}
    virtual void listener() = 0;
};

class B {
public:
    BListener *m_listener;
    
    B(BListener *listener = NULL) {
        m_listener = listener;
    }
    void foo() { //需要访问A中的成员变量
        if(m_listener) {
            m_listener->listener();
        }
    }
};

class A : public BListener {
public:
    void onNotify() {
        //访问A的成员变量 
    }
    void listener() {
        onNotify();
    }
public:
    B b;
};

int main() {
    A a;

    return 0;
}
