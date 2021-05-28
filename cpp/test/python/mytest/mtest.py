#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

try:
    num = int(input("请输入一个数:"))
except:
    info = sys.exc_info()
    print("%s:%s" % (info[0], info[1]))

if num >= 90:
    print("A")
elif num >= 60:
    print("B")
else:
    print("C")
