#!/usr/bin/python3

import sys
from myfun import my_input 

def calculate(num):
    result = 0.0
    start = 1 if num % 2 == 1 else 2
    for i in range(start, num):
        result += 1/i
    return result

if __name__ == '__main__':
    num = my_input("输入一个整数:", 'int')
    print("sum = %f" % calculate(num))

