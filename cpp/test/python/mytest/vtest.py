#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def Factorial(num):
    if num == 1:
        return num
    return num*Factorial(num-1)

if __name__ == "__main__":
    print("result = %d" % Factorial(5))
