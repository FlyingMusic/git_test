#!/usr/bin/python3

import tensorflow as tf
assert tf.__version__.startswith('2.')

#tf.train.GradientDescentOptimizer(learning_rate)

optimizer = tf.train.GradientDescentOptimizer(learning_rate = 0.01)
train_setp = optimizer(loss)

sess = tf.Session()

sess.run(train_step, feed_dict = {X:X_data, Y:Y_data})
sess.close()


