#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    array = [1, 2, 3, 4, 5]
    str = ",".join(str(s) for s in array)
    print(str)

    a = ['1', '2', '3', '4', '5'] 
    str = ",".join(a)
    print(str)
