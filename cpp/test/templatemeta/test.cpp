#include <iostream>

using namespace std;

int add(int a, int b) {
    return a + b; 
}

template<int A, int B>
class Add {
public:
    enum{result = A + B };
};
int main() {
    int a = 2;
    int b = 3;
    int sum = add(a, b);
    printf("sum = %d\n", sum);
    printf("sum = %d\n", Add<2, 3>::result);
    return 0;
}
