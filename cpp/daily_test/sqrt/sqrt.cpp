#include <stdio.h>

#define PRECISION 0.00000001

double mysqrt(int num) {
    double lef = 1.0;
    double rig = num;
    double mid = (lef + rig) / 2.0;
    while(true) {
        if(num - mid*mid > PRECISION) {
            lef = mid;
        } else if (mid*mid - num > PRECISION) {
            rig = mid;
        } else {
            return mid;
        }
        mid = (lef + rig) / 2.0;
        printf("%.10lf\n", mid);
    }
}
int main() {
    printf("%lf\n", mysqrt(2));
    printf("%lf\n", mysqrt(3));
    printf("%lf\n", mysqrt(4));
    return 0;
}
