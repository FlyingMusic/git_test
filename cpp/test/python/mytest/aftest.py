#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import random

def InsertSort2(array):
    for i in range(1, len(array)):
        tmp = array[i]
        j = i - 1
        while j >= 0:
            if array[j] > tmp:
                array[j+1] = array[j]
            else:
                break
            j -= 1
        array[j] = tmp

def InsertSort(array):
    for i in range(1, len(array)):
        tmp = array[i]
        j = 0
        for j in range(i-1, -1, -1):
            if array[j] > tmp:
                array[j+1] = array[j]
            else:
                break
        array[j] = tmp


if __name__ == "__main__":
    array = [3, 2, 1]
    #for i in range(10):
    #    array.append(random.randint(0,9))
    print(array)
    InsertSort(array)
    print(array)

    for i in range(1,3,1):
        print(i)
    print()
    for i in range(3,1,-1):
        print(i)

