#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import random
import time

if __name__ == '__main__':
    num = random.randint(0,51)
    start = time.time()
    while(True):
        try:
            inum = int(input("请输入一个0-50的数："))
        except:
            print("输入有误,请重新输入")
            continue
        if inum < num:
            print("猜小了")
            continue
        if inum > num:
            print("猜大了")
            continue
        print("猜对了: %d " % num)
        break
    end = time.time()
    var = (end - start)
    print(start, end, var)

