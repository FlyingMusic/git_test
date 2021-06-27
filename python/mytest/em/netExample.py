#!/usr/bin/python3

import numpy as np
import random
import math
from scipy import stats

def averageWeight(height, gamma, n):
    mean = 0.0
    for i in range(len(height)):
        mean += height[i] * gamma[i]
    return mean / n

def varianceWeight(height, gamma, mu, n):
    var = 0.0
    for i in range(len(height)):
        var += (height[i] - mu) * (height[i] - mu) * gamma[i]
    return var / n


def isSame(lefarr, rigarr):
    if(len(lefarr) != rigarr):
        return False
    for l,r in zip(lefarr, rigarr):
        if(math.fabs(l - r) > 0.0001):
            return False
    return True

def calcEM(height):
    N = len(height)
    gp = 0.5
    bp = 0.5
    gmu, gsigma = min(height), 10
    bmu, bsigma = max(height), 10
    ggamma = list(range(N))
    bgamma = list(range(N))
    cur = [gp, bp, gmu, gsigma, bmu, bsigma]
    now = []

    times = 0
    while times < 100:
        i = 0
        for x in height:
            ggamma[i] = gp * stats.norm.pdf(x, gmu, gsigma)
            bgamma[i] = bp * stats.norm.pdf(x, bmu, bsigma)
            s = ggamma[i] + bgamma[i]
            ggamma[i] /= s
            bgamma[i] /= s
            i += 1
        gn = sum(ggamma)
        gp = float(gn) / float(N)
        bn = sum(bgamma)
        bp = float(bn) / float(N)
        gmu = averageWeight(height, ggamma, gn)
        gsigma = varianceWeight(height, ggamma, gmu, gn)
        bmu = averageWeight(height, bgamma, bn)
        bsigma = varianceWeight(height, bgamma, bmu, bn)
        
        now = [gp, bp, gmu, gsigma, bmu, bsigma]
        if isSame(cur, now):
            break
        cur = now
        print(times, gmu, gsigma, bmu, bsigma)
        times += 1 
    return now

if __name__=='__main__':
    #模拟产生男女身高各100个
    male_array = np.random.normal(loc = 200, scale = 5.0, size = 100)
    fmale_array = np.random.normal(loc = 100, scale = 5.0, size = 100)
    print(male_array)
    print(fmale_array)

    #混合数据
    merged_array = []
    for i in range(len(male_array)):
        merged_array.append(male_array[i])
        merged_array.append(fmale_array[i])
    print(merged_array)

    calcEM(merged_array)    

