#!/bin/python3
# -*- coding: UTF-8 -*-

import pdb

def is_prime_num(num):
    i = 2
    while i*i <= num:
        if num % i == 0:
            return False
        i += 1;
    return True

def is_narcissus_num(num):
    #pdb.set_trace()
    i = int(num / 100)
    j = int(num / 10 % 10)
    k = int(num % 10)
    if i*i*i + j*j*j + k*k*k == num:
        return True
    return False

def is_perfect_num(num):
    factor_sum = 1
    for i in range(2, num):
        if num % i == 0:
            factor_sum += i
    return True if (num == factor_sum) else False

for i in range(1, 1000):
    if is_perfect_num(i):
        print("%d" % i, end=' ', flush=True)
print()
