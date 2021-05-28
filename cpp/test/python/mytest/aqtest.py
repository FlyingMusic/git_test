#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def Fac(n):
    if n == 1:
        return 1
    else:
        return n*Fac(n-1)
    
def A(n, m):
    result = 1
    for i in range(n-m+1, n+1):
        result *= i
    return result

if __name__ == '__main__':
    sum = 0
    for i in range(1, 9):
        sum += A(8, i)
        print(A(8,i))
    print(sum//2)


