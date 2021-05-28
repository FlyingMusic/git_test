#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def getNthNum(base, num):
    tmp = 0
    for i in range(num):
        tmp *= 10
        tmp += base
    return tmp


if __name__ == "__main__":
    a = 2
    try:
        num = int(input("输入几个数相加:"))
    except:
        info = sys.exc_info()
        print("%s:%s" % (info[0], info[1]))
        sys.exit(-1)
    sum = 0
    for i in range(num):
        sum += getNthNum(a, i+1)

    print("sum = %d" % (sum))

