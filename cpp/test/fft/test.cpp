#include <cstdio>
#include <math.h>

#define Maxn 1000500
#define PI 3.1415926535898

struct complex {
    complex(double xx=0.0, double yy=0.0) : x(xx), y(yy) { }
    double x;
    double y;
};

complex operator + (complex a, complex b) {
    return complex(a.x+b.x, a.y+b.y);
}

complex operator - (complex a, complex b) {
    return complex(a.x-b.x, a.y-b.y);
}

complex operator * (complex a, complex b) {
    return complex(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);
}

complex operator / (complex a, complex b) {
    double t = b.x*b.x + b.y*b.y;
    return complex((a.x*b.x+a.y*b.y)/t, (a.y*b.x-a.x*b.y)/t);
}

complex b[Maxn], tmp, buf;

int n = 0;
int m = 0;

void dft(complex *f, int len) {
    if(len == 0) return;
    complex fl[len+1];
    complex fr[len+1];
    for(int k = 0; k < len; ++k) {
        fl[k] = f[k << 1];
        fr[k] = f[k << 1 | 1];
    }
    dft(fl, len >> 1);
    dft(fr, len >> 1);
    complex tmp, buf;
    len *= 2;
    tmp = complex(cos(2*PI/len), sin(2*PI/len));
    buf.x = 1.0;
    buf.y = 0.0;
    for(int k = 0; k < len/2; ++k) {
        f[k] = fl[k] + buf*fr[k];
        f[k+len/2] = fl[k] - buf*fr[k];
        buf = buf * tmp;
    }
}
int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%lf", &b[i].x);
    }
    for(m = 1; m < n; m <<= 1);
    dft(b, m >>1);
    for(int i = 0; i < m; ++i) {
        printf("%.4f ", b[i].x);
    }
    printf("\n");
    return 0;
}
