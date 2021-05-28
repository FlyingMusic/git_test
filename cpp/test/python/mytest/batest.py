#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import random
import time

if __name__ == '__main__':
    filename = "baresult.txt"
    fp = open(filename,"w")
    string = input("请输出一个字符:")
    string = string.upper()
    fp.write(string)
    fp.close()


    
