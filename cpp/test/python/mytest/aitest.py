#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    while True:
        try:
            num = int(input("请输入一个数:"))
        except:
            info = sys.exc_info()
            print("%s:%s" % (info[0], info[1]))
            break
        result = num * num
        print("%d x %d = %d" % (num, num, num*num))
        if num*num < 50:
            break

