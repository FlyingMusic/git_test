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
    mean = np.mean(X)
    std = np.std(X)
    X = (X - mean)/std
    return X

# Data
data =  pandas.read_csv('./data/housing.csv', sep='\s+')

X_train, Y_train = data['RM'], data['MEDV']

X_train = normalize(X_train)
n_samples = len(X_train)

# PlaceHolder for the Training
X = tf.placeholder(tf.float32, name = 'X')
Y = tf.placeholder(tf.float32, name = 'Y')

# 创建 TensorFlow的权重和偏置变量并初始化为零
b = tf.Variable(0.0)
w = tf.Variable(0.0)

# 定义用于预测的线性回归模型
Y_hat = X * w + b

# 定义 loss function
loss = tf.square(Y - Y_hat, name = 'loss')

# 选择梯度下降优化器
optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.005).minimize(loss)

# 声明初始化操作符
init_op = tf.global_variables_initializer()
total = []

# 开始计算
with tf.Session() as sess:
    # Init variables
    sess.run(init_op)
    writer = tf.summary.FileWriter('graph', sess.graph)
    # train the model for 100 epochs
    for i in range(100):
        total_loss = 0
        for x,y in zip(X_train, Y_train):
            _,l = sess.run([optimizer, loss], feed_dict={X:x, Y:y})
            total_loss += l
        total.append(total_loss/n_samples)
        print('Epoch {0}: Loss {1}'.format(i, total_loss/n_samples))
    writer.close()
    b_value, w_value = sess.run([b, w])

Y_pred = X_train * w_value + b_value
print('Done')

plt.plot(X_train, Y_train, 'bo', label='Real Data')
plt.plot(X_train, Y_pred, 'r', label='Predicted Data')
plt.legend()
plt.savefig("1.png")
plt.plot(total)
plt.savefig("2.png")
print('Hellp tflow')
