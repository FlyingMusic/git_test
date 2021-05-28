#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import re

if __name__ == '__main__':
    list = ['12', "abc", '1', "3"]
    print(list)
    string = ','.join(list)
    print(string)
    
    list = [12, "abc", 1, "34"]
    print(list)
    string = ''
    for i in list:
        string += str(i)
    print(string)

