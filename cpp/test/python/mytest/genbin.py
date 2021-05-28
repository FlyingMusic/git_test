#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def makeLable(instr):
    result = []
    oneNum = 0
    for i in instr:
        if i == '0':
            result.append(0)
        elif i == '1':
            result.append(1)
            oneNum += 1
        else:
            print("invaid input\n")
            sys.exit(-1)
    return result,oneNum

def getValueArr(num, onenum):
    result = []
    mask = 1
    for i in range(0, onenum):
        result.append('0' if mask&num == 0 else '1')
        mask <<= 1
    return result

def getResult(lable, arr):
    result = []
    ai = 0
    for i in lable:
        if i == 1:
            result.append(arr[ai])
            ai += 1
        else:
            result.append('0')
    return result

if __name__ == '__main__':
    instr = input("请输入0/1字符串:")
    print("input:", instr)
    inlen = len(instr)
    print("inlen:", inlen)
    lable,onenum = makeLable(instr)
    print(lable)
    print("one num:", onenum)
    maxvalue = pow(onenum, 2) - 1
    print("max value:", maxvalue)
    for num in range(0, maxvalue+1):
        valuearr = getValueArr(num, onenum)
        result = getResult(lable, valuearr)
        result = ''.join(result)
        print(result)
