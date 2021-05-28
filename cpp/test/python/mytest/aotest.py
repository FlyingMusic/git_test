#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == '__main__':
    for i in range(10, 99):
        if 809*i <= 999 or 809*i > 9999:
            continue
        if 8*i <= 9 or 8*i > 99:
            continue
        if 9*i <= 99 or 9*i > 999:
            continue
        print(i,809*i,8*i,9*i)
