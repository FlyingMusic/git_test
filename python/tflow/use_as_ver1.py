#!/usr/bin/python3

import tensorflow as tf
assert tf.__version__.startswith('2.')
tf.compat.v1.disable_eager_execution()

a = tf.constant(2.)
b = tf.constant(4.)

print('a = ', a)
print('b = ', b)
print()

a = tf.constant([9, 8, 5])
b = tf.constant([2, 1, 1])
print('a = ', a)
print('b = ', b)
print()

a = tf.constant([[1, 2, 3], [4, 5, 6], [7, 8, 9]], tf.float64)
b = tf.constant([[1, 1, 1], [1, 1, 1], [1, 1, 1]], tf.float64)
print('a = ', a)
print('b = ', b)
print("rank(a) = ", tf.rank(a))
print("rank(b) = ", tf.rank(b))
print('a + b = ', a+b)
print('a * b = ', a*b)
print('inv(a) = ', tf.compat.v1.matrix_inverse(a))
