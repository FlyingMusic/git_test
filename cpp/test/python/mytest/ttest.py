#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def getStarNumber(line):
    if line < 0 or line > 7:
        return -1
    if line <= 4:
        return line*2-1
    else:
        return (8-line)*2-1
   
def getStarString(num):
    str = ""
    for i in range(num):
        str += '*'
    return str

if __name__ == "__main__":
    for r in range(1, 8):
        print(getStarString(getStarNumber(r)).center(7," "))
