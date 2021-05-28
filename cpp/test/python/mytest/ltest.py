#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

try:
    num = int(input("请输入一个数:"))
except:
    info = sys.exc_info()
    print("%s:%s" % (info[0], info[1]))

print(type(num))

print(num,"= ", end='')

is_stop = False
while is_stop is False:
    for i in range(2, (num)):
        if num % i == 0:
            print(i,"* ",end='')
            num //= i
            break
    if i == num-1:
        is_stop = True
print(num)
