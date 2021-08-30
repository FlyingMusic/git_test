#include <iostream>
#include <thread>

using namespace std;

template <typename T>
class Singleton
{
public:
    static T& getInstance()
    {
        static T s_Instance;
        return s_Instance;
    }

protected:
    Singleton(void) { cout << "Singleton..." << endl; }
    ~Singleton(void) { cout << "~Singleton..." << endl;}

private:
    Singleton(const Singleton& rhs) {}
    Singleton& operator= (const Singleton& rhs) {}
};

class MyClass : public Singleton<MyClass> {


};
int func() {
    MyClass &mc = MyClass::getInstance();
}

int main() {

    std::thread t[10];

    for (int i = 0; i < 10; ++i) {
        t[i] = std::thread(func);
    }

    for (int i = 0; i < 10; ++i) {
          t[i].join();
    }
    return 0;
}
