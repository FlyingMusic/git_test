#!/usr/bin/python3

import numpy as np

x = [3.3,4.4,5.5,6.71,6.93,4.168,9.779,6.182,7.59,2.167,
                  7.042,10.791,5.313,7.997,5.654,9.27,3.1]
y = [1.7,2.76,2.09,3.19,1.694,1.573,3.366,2.596,2.53,1.221,
                  2.827,3.465,1.65,2.904,2.42,2.94,1.3]

# 为使用numpy库计算平均值，将数据转为np.array格式，当然也可以使用循环计算和再除个数的方式计算平均值
x = np.array(x)
y = np.array(y)

# 调用numpy的mean函数计算平均值
x_avg = np.mean(x)
y_avg = np.mean(y)

# 根据公式计算b的分子和分母
b_top = 0.0
b_bottom = 0.0

for _x, _y in zip(x, y):
    b_top += (_x - x_avg) * (_y - y_avg)
    b_bottom += (_x - x_avg) * (_x - x_avg) 

# 得到b
b = b_top/b_bottom

# 计算a
a = y_avg - b*x_avg

print('b = ', b)
print('a = ', a)

def get_loss(y, y_pred):
    return (y - y_pred)*(y - y_pred)

loss = 0.0
for _x, _y in zip(x, y):
    loss += get_loss(_y, _x*b + a)

print('loss = ', loss)
