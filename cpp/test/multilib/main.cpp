#include <stdio.h>

int add(int lef, int rig);
int sub(int lef, int rig);

int add1(int lef, int rig);
int sub1(int lef, int rig);

int add2(int lef, int rig);
int sub2(int lef, int rig);

int main() {
    printf("%d\n", add(3, 4));
    printf("%d\n", sub(3, 4));
    printf("%d\n", add1(3, 4));
    printf("%d\n", sub1(3, 4));
    printf("%d\n", add2(3, 4));
    printf("%d\n", sub2(3, 4));
    return 0;
}
