#!/usr/bin/python3

import tensorflow as tf
import numpy as np

'''
GradientTape是tf中的上下文管理器，用来连接需要计算梯度的函数和变量

'''

x = tf.constant(3.0)

with tf.GradientTape() as g:
    g.watch(x)
    y = x * x
dy_dx = g.gradient(y, x)

print('dy/dx(x = 3) = ', dy_dx)
