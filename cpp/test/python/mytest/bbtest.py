#!/bin/python3
# -*- coding: UTF-8 -*-

import sys

if __name__ == '__main__':
    filename_inA = "bbinputA.txt"
    filename_inB = "bbinputB.txt"
    filename_out = "bbresult.txt"
    fpinA = open(filename_inA,"r")
    fpinB = open(filename_inB,"r")
    fpout = open(filename_out,"w")
    #stringA = fpinA.read()
    #stringB = fpinB.read()
    string = []
    string.append(fpinA.read().replace('\n',''))
    string.append(fpinB.read().replace('\n',''))
    string.sort()
    print(string)
    fpout.write(','.join(string))
    fpinA.close()
    fpinB.close()
    fpout.close()
