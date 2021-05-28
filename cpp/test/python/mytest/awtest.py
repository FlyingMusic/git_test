#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def encode(num):
    result = 0
    bit0 = num % 10
    bit1 = num // 10 %10
    bit2 = num // 100 % 10
    bit3 = num // 1000 % 10
    bit0 = (bit0 + 5) % 10
    bit1 = (bit1 + 5) % 10
    bit2 = (bit2 + 5) % 10
    bit3 = (bit3 + 5) % 10
    bit0, bit3 = bit3, bit0
    bit1, bit2 = bit2, bit1
    result += bit0 + bit1*10 + bit2*100 + bit3*1000
    return result

if __name__ == '__main__':
    try:
        num = int(input("请输入一个4位的整数:"))
    except:
        print("无效输入")
        sys.exit(-1)
    if num < 1000 or num > 9999:
        print("无效输入")
        sys.exit(-1)
    print("encode: %d" % encode(num))
        
