#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == '__main__':
    try:
        num = int(input("请输入一个奇数:"))
    except:
        printf("无效输入")
        sys.exit(-1)
    if(num % 2 != 1):
        printf("无效输入")
        sys.exit(-1)
    result = 9
    while(True):
        if result % num == 0:
            print(result, result//num)
            break
        result *= 10
        result += 9




