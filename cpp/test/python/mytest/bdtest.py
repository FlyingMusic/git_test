#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

class MyClass:
    m = 1
    n = 2
    def __init__(self):
        self.m = 0
        self.n = 0
    def __str__(self):
        return "%d,%d" % (self.m, self.n)
    def __eq__(self, other):
        return self.m == other.m and self.n == other.n
    
if __name__ == '__main__':
    a = 1
    b = 1
    print("a:", a)
    print("b:", b)
    print("a == b:", a==b)
    print("a is b:", a is b)

    a = 1000
    b = 1000
    print("a:", a)
    print("b:", b)
    print("a == b:", a==b)
    print("a is b:", a is b)
    
    a = 1.123
    b = 1.123
    print("a:", a)
    print("b:", b)
    print("a == b:", a==b)
    print("a is b:", a is b)
    

    a = "abcd"
    b = "abcd"
    print("a:", a)
    print("b:", b)
    print("a == b:", a==b)
    print("a is b:", a is b)

    
    a = (1, 2, 3)
    b = (1, 2, 3)
    print("a:", a)
    print("b:", b)
    print("a == b:", a==b)
    print("a is b:", a is b)
    
    a = [1, 2, 3]
    b = [1, 2, 3]
    print("a:", a)
    print("b:", b)
    print("a == b:", a==b)
    print("a is b:", a is b)
    
    a = MyClass()
    b = a
    print("a:", a)
    print("b:", b)
    print("a == b:", a==b)
    print("a is b:", a is b)
