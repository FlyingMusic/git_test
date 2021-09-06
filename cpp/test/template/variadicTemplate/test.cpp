#include <stdio.h>
#include <tuple>

using namespace std;

class Test {
private:
    int m_a;
};
int main() {
    //tuple<Test*, string, int, double> mtuple{new Test(), "hello", 5, 7.999};
    auto mtuple = make_tuple(new Test(), "hello", 5, 7.999);
    int& a = get<2>(mtuple);
    printf("a = %d\n", a);
    a++;
    int& b = get<2>(mtuple);
    printf("b = %d\n", b);

    return 0;
}

