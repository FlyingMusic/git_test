#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == "__main__":
    for a in ('y', 'z'):
        for b in ('x', 'y', 'z'):
            for c in ('y'):
                if a==b or a==c or b==c:
                    continue
                print('a',a)
                print('b',b)
                print('c',c)

