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
    if num%10 == num//10000 and num//10%10 == num//1000%10:
        print("%d是回文数" % (num))
    else:
        print("%d不是回文数" % (num))
