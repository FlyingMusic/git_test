#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

def foo():
    ver = 0
    print(ver)
    ver += 1

class Static:
    staticVer = 0
    def foo(self):
        print(self.staticVer)
        self.staticVer += 1

if __name__ == "__main__":
    for i in range(3):
        foo()

    s = Static()
    for i in range(3):
        s.foo()




