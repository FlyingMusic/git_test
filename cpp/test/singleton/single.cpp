#include <iostream>
#include <thread>

using namespace std;

class Single {
public:
    ~Single() { cout << "~Single" << endl; }
    static Single& getInstance() {
        static Single single;
        return single;
    }
private:
    Single(const Single&) = delete;
    Single& operator=(const Single&) = delete;
    Single() { cout << "Single" << endl;}
};

class UserClass : public Single {

};
int func() {
    Single &pSingl = Single::getInstance();
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
