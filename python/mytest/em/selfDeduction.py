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
    if(len(lefarr) != len(rigarr)):
        return False
    for l,r in zip(lefarr, rigarr):
        if(math.fabs(l - r) > 0.00001):
            return False
    return True

def calcEM(height):
    N = len(height)
    gp = 0.5
    bp = 0.5
    gmu, gsigma = min(height), 1
    bmu, bsigma = max(height), 1
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
         
        print(ggamma[0:4])
        print(bgamma[0:4])
        gmu = averageWeight(height, ggamma, gn)
        gsigma = varianceWeight(height, ggamma, gmu, gn)
        bmu = averageWeight(height, bgamma, bn)
        bsigma = varianceWeight(height, bgamma, bmu, bn)
        
        now = [gp, bp, gmu, gsigma, bmu, bsigma]
        if isSame(cur, now):
            break
        cur = now
        print()
        print(gmu, gsigma, bmu, bsigma)
        times += 1 
    return now

def myEM(height):
    N = len(height)
    # 假设两个分布的参数已知
    gmu, gsigma = 150, 10
    bmu, bsigma = 200, 10

    for i in range(100):
        # 计算参数下的权重分配
        gweight = []
        bweight = []
        for h in height:
            gw = stats.norm.pdf(h, gmu, gsigma)
            bw = stats.norm.pdf(h, bmu, bsigma)
            gweight.append(gw / (gw + bw))
            bweight.append(bw / (gw + bw))
        #print(gweight)
        #print(bweight)

        # 用新权重更新参数
        wsum = 0.0
        gmuSum = 0.0 
        for h,w in zip(height, gweight):
            gmuSum += h * w
            wsum += w

        gmu = gmuSum / wsum
       # print("gmu = %f\n" % gmu)

        gsigmaSum = 0.0
        for h,w in zip(height, gweight):
            gsigmaSum += (h - gmu) * (h - gmu) * w
        gsigma = gsigmaSum / wsum
        gsigma = math.sqrt(gsigma)
       # print("gsigma = %f\n" % gsigma)


        wsum = 0.0
        bmuSum = 0.0 
        for h,w in zip(height, bweight):
            bmuSum += h * w
            wsum += w

        bmu = bmuSum / wsum
       # print("bmu = %f\n" % bmu)

        bsigmaSum = 0.0
        for h,w in zip(height, bweight):
            bsigmaSum += (h - bmu) * (h - bmu) * w
        bsigma = bsigmaSum / wsum
        bsigma = math.sqrt(bsigma)
       # print("bsigma = %f\n" % bsigma)

        print("gmu[%f] gsigma[%f] bmu[%f] bsigma[%f]\n" % (gmu, gsigma, bmu, bsigma))

if __name__=='__main__':
    #模拟产生男女身高各100个
    male_array = np.random.normal(loc = 165, scale = 5.0, size = 1000)
    fmale_array = np.random.normal(loc = 175, scale = 5.0, size = 1000)
    #print(male_array)
    #print(fmale_array)

    #混合数据
    merged_array = []
    for i in range(len(male_array)):
        merged_array.append(male_array[i])
        merged_array.append(fmale_array[i])
   # print(merged_array)
    merged_array.sort()
    print(merged_array)

    myEM(merged_array)    

