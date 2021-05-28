#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == '__main__':
    testList = [10086,'中国移动',[1,2,3,4,5,'a']]
    print(len(testList))
    print(testList)
    print(testList[:])
    print(testList[1:])
    print(testList[:1])
        
    print(testList.pop(1))
    print(len(testList))
    print(testList)
    matrix = [[1,2,3], [4,5,6], [7,8,9]]
    col2even = [row[1] for row in matrix if  row[1] % 2 == 0]
    print(col2even)

