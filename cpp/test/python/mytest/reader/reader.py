#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import re
import numpy as np

if __name__ == "__main__":
    data = []
    with open('data.txt', 'r') as f:
        for idata in f:
            data.append(re.split("[ \n]", idata.strip()))

    data = np.array(data)
    print(data[:,2])
