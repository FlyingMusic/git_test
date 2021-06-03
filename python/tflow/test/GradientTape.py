#!/usr/bin/python3

import tensorflow as tf
import numpy as np

'''
GradientTape是tf中的上下文管理器，用来连接需要计算梯度的函数和变量

程序输出如下：
x =  <tf.Variable 'Variable:0' shape=() dtype=float32, numpy=3.0>
y =  tf.Tensor(9.0, shape=(), dtype=float32)
dy/dx(x = 3) =  tf.Tensor(6.0, shape=(), dtype=float32)

首先要明确的是，我们不能对一个数求导，我们只能对一个函数的某个变量求导，这在数学上
是非常直接明了的，但在计算的coding中却显得比较怪，当我们执行g.gradient(y, x)时，y和x的类型就
比较怪异，如果从纯数学角度来说，y其实是个函数，而x是其变量，但一般的数值计算是不存
在这种概念的，而这恰恰是tf解决的问题，它定义了张量的概念，让我们可以直接写gradient(y, x)
其中y就是张量，从打印来看，张量有一个数值（9.0）但它又不仅仅是一个数值（再说一次，
没办法对一个数求导），它跟其定义x*x是有某种关联的，这种关联就是所谓的计算图完成的
这让变编程最大程度上简化了，这也是TF最牛的地方之一
'''

x = tf.Variable(3.0)
#x = tf.constant(3.0)

def gety(x):
    return x*x

with tf.GradientTape() as g:
    y = gety(x)
    print('x = ', x)
    print('y = ', y)
    dy_dx = g.gradient(y, x)
    print('dy/dx(x = 3) = ', dy_dx)

