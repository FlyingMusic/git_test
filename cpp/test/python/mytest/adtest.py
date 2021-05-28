#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import random

def BubbleSort(array):
    for i in range(len(array)):
        for j in range(len(array)-i-1):
            if array[j] > array[j+1]:
                array[j], array[j+1] = array[j+1], array[j]

if __name__ == "__main__":
    array = []
    for i in range(10):
        array.append(random.randint(0,9))
    print(array)
    BubbleSort(array)
    print(array)
