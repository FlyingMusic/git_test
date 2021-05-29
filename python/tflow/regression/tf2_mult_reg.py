#!/usr/bin/python3

import tensorflow as tf
import numpy as np
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import pandas

learning_rate = 0.01
traing_steps = 1000
display_step = 50

def normalize(X):
    """ normalizes the array X """
    mean = np.mean(X, axis=0)
    std = np.std(X, axis=0)
    X = (X - mean)/std
    return X

def append_bias_reshape(features, lables):
    m = features.shape[0]
    n = features.shape[1]
    x = np.reshape(np.c_[np.ones(m), features], [m, n+1])
    y = np.reshape(lables, [m, 1])
    return x, y

# Data
data =  pandas.read_csv('./data/housing.csv', sep='\s+')

X_train, Y_train = data.iloc[:,0:data.shape[1] - 1], data['MEDV'] #pandas返回的结果是个对象，取固定几列有固定方法

X_train = np.array(X_train)
Y_train = np.array(Y_train)

X_train = normalize(X_train)
X_train, Y_train = append_bias_reshape(X_train, Y_train)

m = len(X_train)
n = 13 + 1

# 创建 TensorFlow的权重和偏置变量并初始化为零
b = tf.Variable(0.0)
w = tf.Variable(tf.random_normal([n, 1]))

# 线性回归函数
def linear_regression(x):
    return w*x +b

# 定义 loss function
def mean_square(y_pred, y_true):
    return tf.reduce_mean(tf.pow(y_pred-y_true, 2) / (2*m))

# 选择梯度下降优化器
optimizer = tf.optimizers.SGD(learning_rate=0..05)

# 计算梯度，更新参数
def run_optimizztion():
    # tf.GrandientTap()梯度带，可以查看每一次epoch的参数
    with tf.GradientTape() as g:
        pred = linear_regression(X_train)
        loss = mean_square(pred, Y_train)
    # 计算梯度
    gradients = g.gradient(loss, [w, b])

    #更新 w, b
    optimizer.apply_gradients(zip(gradients, [w, b]))
    

# 开始计算
for step in range(1, training_steps+1):
    run_optimization()
    if step % display_step == 0:
        pred = linear_regression(X_train)
        loss = mean_square(pred, Y_train)
        print("step: %i, loss %f, w: %f, b: %f" % (step, loss, w.numpy(), b.numpy()))
