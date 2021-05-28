#!/bin/python3
# -*- coding: UTF-8 -*-

import sys
import re

if __name__ == '__main__':
    str = '找到北京市通州区中山大街59号院1号楼的肯德基中山大街餐厅等多个结果，需要将哪一个添加到途经点？'
    format = r'找到.*等多个结果，需要将哪一个添加到途经点？'
    matchObj = re.search(format,str)
    if matchObj:
        print("search --> searchObj.group() : ", matchObj.group())
    else:
        print("No match!!")
