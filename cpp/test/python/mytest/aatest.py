#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    array = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    # 全部遍历
    for i in array:
        print(i, end=' ')
    print()
    
    # 部分
    for i in array[1:3]:
        print(i, end=' ')
    print()
   
   # 倒序
    for i in array[::-1]:
        print(i, end=' ')
    print()

    # 部分倒序
    for i in array[3:1:-1]:
        print(i, end=' ')
    print()


    
