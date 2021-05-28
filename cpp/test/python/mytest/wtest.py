#!/bin/python3
# -*- coding: UTF-8 -*-

import sys


def reverse(cnt):
    if cnt == 5:
        return
    a = int(input("请输入第%d个数:" % (cnt+1)))
    reverse(cnt+1)
    print("第%d个数是: %d" % (cnt+1, a))

if __name__ == "__main__":
    reverse(0)
