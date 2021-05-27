#!/usr/bin/python3
# -*- coding: UTF-8 -*-

import time

if __name__ == '__main__':
    left = 4
    sum = 0
    while(True):
        sum = left
        i = 0
        for i in range(5):
            sum = sum//4*5 + 1
            if sum % 4 != 0:
                break
        if i == 4:
            break
        left += 4
    print("left = %d" % left)
    print("sum = %d" % sum)
