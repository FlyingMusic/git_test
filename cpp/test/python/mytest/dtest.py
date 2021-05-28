#!/bin/python
# -*- coding: UTF-8 -*-

import sys

a = []

for i in range(0, 3):
    try:
        a.append(int(raw_input("第%d个数: " % (i+1))))
    except ValueError:
        info = sys.exc_info()
        print info[0],":",info[1]
        sys.exit(-1)

min = (a[0] if a[0] < a[2] else a[2]) if (a[0] < a[1]) else (a[1] if a[1] < a[2] else a[2])
max = (a[0] if a[0] > a[2] else a[2]) if (a[0] > a[1]) else (a[1] if a[1] > a[2] else a[2])

print min, a[0]+a[1]+a[2]-min-max, max


b = []
b.append(1)
b.append('a')
b.append(1)
b.append("a")
b.append('a')

print b

print = 2
print print
