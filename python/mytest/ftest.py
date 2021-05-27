#!/usr/bin/python3
# -*- coding: UTF-8 -*-
 
from myfun import my_input

if __name__ == '__main__':
    strings = []
    for i in range(5):
        strings.append(my_input("please input a string:"))
    strings.sort()
    print(strings)
