#!/bin/python
# -*- coding: UTF-8 -*-

a1 = 0
a2 = 1

print a1, a2,

for i in range(100):
    a3 = a1 + a2
    print a3,
    a1 = a2
    a2 = a3
