#!/bin/python
# -*- coding: UTF-8 -*-

for i in range(1,168):
    for j in range(i,168):
        if (i+j)*(j-i) == 168:
            print i,j
