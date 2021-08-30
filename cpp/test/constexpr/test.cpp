#include <iostream>

using namespace std;

int foo(int num) {
    return num == 1 ? num : num + foo(num-1);
}
constexpr int cefoo(int num) {
    return num == 1 ? num : num + cefoo(num-1);
}
int main(int argc, char *argv[]) {
    //int a[foo(10)] = {0}; //编译失败
    int b[cefoo(10)] = {0}; //编译成功
    //int c[cefoo(argc)] = {0}; //编译失败
    printf("%d\n", cefoo(argc)); //编译成功
    return 0;
}
