#!/bin/python3
# -*- coding: UTF-8 -*-

import sys


if __name__ == "__main__":
    sum = 1
    for i in range(10):
        print("倒数第%d天剩下的桃子数量为：%d" % (i+1, sum))
        sum = (sum+1)*2

