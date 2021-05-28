#!/bin/python
# -*- coding: UTF-8 -*-

a = 1
b = 1

for i in range(1, 10):
    for j in range(1, i+1):
        print "%d x %d = %d\t" % (i, j, i*j),
    print
