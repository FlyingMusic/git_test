#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import pandas
import numpy as np

if __name__ == "__main__":
    data = pandas.read_csv('data.txt', sep='\s+')
    print(data['b'])
