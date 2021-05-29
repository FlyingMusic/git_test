#!/usr/bin/python3

import math

# 初始坐标
b = 1.0
a = 1.0

# 搜索步长
step = 0.000001
stop_len = 0.000000001

# data
x = [3.3,4.4,5.5,6.71,6.93,4.168,9.779,6.182,7.59,2.167,
                  7.042,10.791,5.313,7.997,5.654,9.27,3.1]
y = [1.7,2.76,2.09,3.19,1.694,1.573,3.366,2.596,2.53,1.221,
                  2.827,3.465,1.65,2.904,2.42,2.94,1.3]

def gradientb(b, a): #对b的偏导
    ans = 0
    for _x, _y in zip(x, y):
        ans += ((b * _x + a) - _y) * _x
    return ans

def gradienta(b, a):#对a的偏导
    ans = 0
    for _x, _y in zip(x, y):
        ans += (b * _x + a) - _y
    return ans

for i in range(0,10000):#梯度下降
    nextb = b - step*gradientb(b, a)
    nexta = a - step*gradienta(b, a)
    b = nextb
    a = nexta


def get_loss(y, y_pred):
    return (y - y_pred)*(y - y_pred)

loss = 0.0
for _x, _y in zip(x, y):
    loss += get_loss(_y, _x*b + a)

print('b = %f, a = %f, loss = %f' % (b, a, loss/len(x)))
