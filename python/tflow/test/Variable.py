#!/usr/bin/python3

import tensorflow as tf
import numpy as np

a = tf.Variable(0.5)
l = 2.3
r = a * l

print("a = ", a)
print("l = ", l)
print("r = ", r)
print()

a = tf.Variable(0.5)
l = [2.3, 1.3, 0.3]
r = a * l

print("a = ", a)
print("l = ", l)
print("r = ", r)
print()

a = tf.Variable(np.random.randn())
l = [2.0, 2.0, 2.0]
r = a * l

print("a = ", a)
print("l = ", l)
print("r = ", r)
print()
