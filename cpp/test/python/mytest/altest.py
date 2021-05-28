#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == '__main__':
    yanghui = []
    row = []
    for r in range(1, 11):
        for l in range(r):
            if l == 0 or l == r-1:
                row.append(1)
            else:
                row.append(yanghui[r-2][l-1] + yanghui[r-2][l])
        yanghui.append(row)
        row = []
    for yh in yanghui:
        print(" ".join(str(s) for s in yh).center(25, " "))
