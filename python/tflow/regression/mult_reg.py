#!/usr/bin/python3

import tensorflow.compat.v1 as tf
tf.disable_v2_behavior()
import numpy as np
import matplotlib as mpl
mpl.use('Agg')
import matplotlib.pyplot as plt
import pandas

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

# PlaceHolder for the Training
X = tf.placeholder(tf.float32, shape = [1, n], name = 'X')
Y = tf.placeholder(tf.float32, name = 'Y')

# 创建 TensorFlow的权重和偏置变量并初始化为零
b = tf.Variable(0.0)
w = tf.Variable(tf.random_normal([n, 1]))

# 定义用于预测的线性回归模型
Y_hat = tf.reduce_mean(tf.matmul(X, w) + b)

# 定义 loss function
loss = tf.square(Y - Y_hat, name = 'loss')

# 选择梯度下降优化器
optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.005).minimize(loss)

# 声明初始化操作符
init_op = tf.global_variables_initializer()
loss_arr = []

# 开始计算
with tf.Session() as sess:
    # Init variables
    sess.run(init_op)
    writer = tf.summary.FileWriter('graph', sess.graph)
    # train the model for 100 epochs
    for i in range(100):
        total_loss = 0
        for x,y in zip(X_train, Y_train):
            x = np.reshape(x, [1, n])
            _,l = sess.run([optimizer, loss], feed_dict={X:x, Y:y})
            total_loss += l
        loss_arr.append(total_loss/m)
        print('Epoch {0}: Loss {1}'.format(i, total_loss/m))
    writer.close()
plt.plot(loss_arr)
plt.savefig("3.png")
