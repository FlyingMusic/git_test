#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def getNthHigh(high, n):
    for i in range(n):
        high /= 2
    return high


if __name__ == "__main__":
    sum = 100
    for i in range(9):
        high = getNthHigh(100,i+1)
        print("第%d次反弹高度为：%f" % (i+1, high))
        sum += 2*high
    print("sum = %f" % (sum))
    print("第10次反弹高度为：%f" % getNthHigh(100, 10))

