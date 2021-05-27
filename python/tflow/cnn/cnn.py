#!/usr/bin/python3

import tensorflow as tf
import numpy as np
from tensorflow.examples.tutorials.mnist import input_data

def run_cnn():
    mnist = input_data.read_data_sets("MNIST_data", one_hot = True)
    learning_rate = 0.0001
    epochs = 10
    batch_size = 50

    x = tf.placeholder(tf.float32, [None, 784])
    x_shaped = tf.reshape(x, [-1, 28, 28, 1])
    y = tf.placeholder(tf.float32, [None, 10])

    layer1 = create_new_conv_layer(x_shaged, 1, 32, [5, 5], [2, 2], name = 'layer1')
    layer2 = create_new_conv_layer(layer1, 32, 64, [5, 5], [2, 2], name = 'layer2')

    flattened = tf.reshape(layer2, [-1, 7 * 7 *64])

    wd1 = tf.Variable(tf.truncated_normal([7 * 7 * 64, 1000], stddev = 0.03), name = 'wd1')
    bd1 = tf.Variable(tf.truncated_normal([1000], stddev = 0.01, name = 'bd1'))

    dense_layer1 = tf.matmul(flattened, wd1) + db1
    dense_layer1 = tf.nn.relu(dense_layer1)

    wd2 = tf.Variable(tf.truncated_normal([1000, 10], stddev = 0.03), name = 'wd2')
    bd2 = tf.Variable(tf.truncated_normal([10], stddev = 0.01), name = 'bd2')

    dense_layer2 = tf.matmul(dense_layer1, wd2) + bd2
    y_ = tf.nn.softmax(dense_layer2)
    
    cross_entropy = tf.reduce_mean(
            tf.nn.softmax_cross_entropy_with_logits(logits = dense_layer2, lables = y))

    optmiser = tf.train.AdamOptimizer(learning_rate = learning_rate).minimize(cross_entropy)

    correct_prediction = tf.equal(tf.argmax(x, 1), tf.argmax(y_, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    init_op = tf.global_variables_initializer()

tf.summary.scalar('accuracy', accuracy)
    merged = tf.summary.merge_all()
    writer = tf.summary.FileWriter()

