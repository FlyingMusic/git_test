#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def MatrixAdd(lef, rig):
    result = []
    row = []
    for i in range(len(lef)):
        for j in range(len(lef[0])):
            row.append(lef[i][j] + rig[i][j])
        result.append(row)
        row = []
    return result

if __name__ == "__main__":
    a = [[1,2,3],[4,5,6],[7,8,9]]
    b = [[11,12,13],[14,15,16],[17,18,19]]
    c = MatrixAdd(a, b)
    print(a)
    print(b)
    print(c)






