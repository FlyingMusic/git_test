#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import random

def reverse(array, m, n):
    n -= 1
    while m < n:
        array[m], array[n] = array[n], array[m]
        m += 1
        n -= 1

if __name__ == '__main__':
    a = []
    n = 20
    m = 5
    for i in range(n):
        a.append(random.randint(0,n))
    print(a)

    reverse(a, 0, m)
    reverse(a, m, len(a))
    reverse(a, 0, len(a))
    print(a)
    
