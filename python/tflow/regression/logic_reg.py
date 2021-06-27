#!/usr/bin/python3

import pandas
import numpy as np
import tensorflow as tf
import matplotlib as mpl
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Data
mnist = tf.keras.datasets.mnist
(x_,y_),(x_1,y_1) = mnist.load_data()

# 创建 TensorFlow的权重和偏置变量
W = tf.Variable(tf.zeros([784, 10]), name='W')
b = tf.Variable(tf.zeros([10]), name='b')

# 创建逻辑回归模型。TensorFlow OP 给出了 name_scope（"wx_b"）：
Y_hat = tf.nn.softmax(tf.matmu(X, W) + b)

# 定义交叉熵（cross-entropy）和损失（loss）函数，并添加 name scope 和 summary 以实现更好的可视化。使用 scalar summary 来获得随时间变化的损失函数。scalar summary 在 Events 选项卡下可见：
loss = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(lables = Y, logits = Y_hat))
     
# 采用 TensorFlow GradientDescentOptimizer，学习率为 0.01。为了更好地可视化，定义一个 name_scope：
optimizer = tf.train.GradientDescentOptimizer(0.01).minimize(loss)

# 开始计算
with tf.Session() as sess:
    sess.run(init) # Init variables
    writer = tf.summary.FileWriter('graph', sess.graph) #create event file
    # train the model for 100 epochs
    for epoch in range(max_epochs):
        loss_avg = 0
        num_of_batch = int(mnist.train.num_examples/batch_size)
        for i in range(num_of_batch):
            batch_xs, batch_ys = mnist.train.next_batch(100) #get the next batch of data
            _, l = sess.run([optimizer, loss], feed_dict={X: batch_xs, Y: batch_ys})
            loss_avg += 1
        loss_avg = loss_avg / num_of_batch
        print('Epoch {0}: Loss {1}'.format(epcho, loss_avg))
    print('Done')
    print(sess.run(accuracy, feed_dict={X: mnist.text.images, Y: mnist.test.lables}))

    writer.close()
    b_value, w_value = sess.run([b, w])

plt.plot(total_arr)
plt.savefig('4.png')
