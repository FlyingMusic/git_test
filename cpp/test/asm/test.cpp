#include <iostream>

int main() {
    int a = 0;
    _asm mov eax, 1;
    _asm mov ecx, 1;
    _asm mov edx, 3;
    //eax==ecx，所以会把edx的值给ecx
    _asm cmpxchg ecx, edx;
    // 打印eax的值=3
    _asm mov a, ecx;
    std::cout << a << std::endl;
}

