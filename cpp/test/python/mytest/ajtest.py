#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    maxlmda = lambda x,y : x if x > y else y
    minlmda = lambda x,y : x if x < y else y

    print(maxlmda(10,20))
    print(minlmda(10,20))

