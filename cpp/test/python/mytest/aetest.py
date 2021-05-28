#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import random

if __name__ == "__main__":
    array = []
    tmp = []
    n = 4
    for i in range(n*n+1):
        tmp.append(random.randint(0,9))
        if (i+1) % n == 0:
            array.append(tmp)
            tmp = []
    for a in array:
        print(a)
    sum = 0
    for i in range(len(array)):
        sum += array[i][i]
    print(sum)

