#!/bin/python3
# -*- coding: UTF-8 -*-

import sys


def reverse(cnt):
    if cnt == 5:
        return
    a = int(input("请输入第%d个数:" % (cnt+1)))
    reverse(cnt+1)
    print("第%d个数是: %d" % (cnt+1, a))

if __name__ == "__main__":
    try:
        num = int(input("请输入一个数字:"))
    except:
        info = sys.exc_info()
        print("%s:%s" % (info[0], info[1]))
        sys.exit(-1)
    digit_number = 0
    num_copy = num
    while num > 0:
        print(num%10)
        num //= 10
        digit_number += 1
    print("%d是%d位数" % (num_copy, digit_number))
