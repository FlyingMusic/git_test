#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    num = 87654321
    print(num)
    num >>= 3
    print(num)
    mask = ~(~0<<4)
    num &= mask
    print(num)

