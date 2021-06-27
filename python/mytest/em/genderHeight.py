#!/usr/bin/python3

import numpy as np
import random
from scipy import stats

if __name__=='__main__':
    #模拟产生男女身高各100个
    male_array = np.random.normal(loc = 175, scale = 5.0, size = 10)
    fmale_array = np.random.normal(loc = 165, scale = 5.0, size = 10)
    print(male_array)
    print(fmale_array)

    #混合数据
    merged_array = []
    for i in range(len(male_array)):
        merged_array.append(male_array[i])
        merged_array.append(fmale_array[i])
    print(merged_array)

    #初始值
    male_m = 1000
    male_v = 10
    fmale_m = 2000
    fmale_v = 10

    # E-step
    male_e = 0.0
    fmale_e = 0.0
    for high in merged_array:
        male_e += high*stats.norm.pdf(high, male_m, male_v)
        fmale_e += high*stats.norm.pdf(high, fmale_m, fmale_v)

    # M-step
    male_m = 




    




