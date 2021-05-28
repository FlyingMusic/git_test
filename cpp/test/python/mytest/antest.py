#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import random

if __name__ == '__main__':
    a = []
    for i in range(10):
        a.append(random.randint(0,9))
    print(a)
    minIndex = 0
    maxIndex = 0
    for i in range(1, len(a)):
        if a[i] < a[minIndex]:
            minIndex = i
        if a[i] > a[maxIndex]:
            maxIndex = i
    a[0], a[maxIndex] = a[maxIndex], a[0]
    a[len(a)-1], a[minIndex] = a[minIndex], a[len(a)-1]
    print(a)
