#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == '__main__':
    try:
        num = int(input("请输入一个1-50的整数:"))
    except:
        print("无效输入")
        sys.exit(-1)
    for i in range(num):
        print('*',end='')
    print()





