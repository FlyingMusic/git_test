#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    w = input("请输入第一个字母:")
    if w == 'M':
        print("星期一")
    elif w == 'T':
        k = input("请输入第二个字母:")
        if k == 'u':
            print("星期二")
        elif k == 'h':
            print("星期四")
    elif w == 'W':
        print("星期三")
    elif w == 'F':
        print("星期五")
    elif w == 'S':
        k = input("请输入第二个字母:")
        if k == 'a':
            print("星期六")
        elif k == 'u':
            print("星期日")
 
