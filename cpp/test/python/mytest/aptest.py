#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == '__main__':
    #num = input("请输入一个八进制数:")
    try:
        num = int(input("请输入一个八进制数:"), 8)
    except:
        print("输入的不是八进制数")
        sys.exit(-1)
    print(num)
