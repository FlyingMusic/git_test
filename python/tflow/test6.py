#!/usr/bin/python3

import tensorflow as tf
assert tf.__version__.startswith('2.')
tf.compat.v1.disable_eager_execution()


sess = tf.compat.v1.InteractiveSession()

I_matrix = tf.eye(5)
print(I_matrix.eval())

X = tf.Variable(tf.eye(10))
X.initializer.run()
print(X.eval())

A = tf.Variable(tf.compat.v1.random_normal([5, 10]))
A.initializer.run()
print(A.eval())

product = tf.matmul(A, X)
print(product.eval())

b = tf.Variable(tf.compat.v1.random_uniform([5, 10], 0, 2, dtype = tf.int32))
b.initializer.run()
print(b.eval())

b_new = tf.cast(b, dtype = tf.float32)

t_sum = tf.add(product, b_new)
t_sub = product - b_new

print("A*X + b\n", t_sum.eval())
print("A*X - b\n", t_sub.eval())

print()

#按照元素操作

a = tf.Variable(tf.compat.v1.random_normal([4, 5], stddev = 2))
b = tf.Variable(tf.compat.v1.random_normal([4, 5], stddev = 2))

A = a * b

B = tf.scalar_mul(2, A)

C = tf.compat.v1.div(a, b)

D = tf.compat.v1.mod(a, b)

init_op = tf.compat.v1.global_variables_initializer()

sess = tf.compat.v1.Session()
sess.run(init_op)
wirter = tf.compat.v1.summary.FileWriter('graphs', sess.graph)
a, b, A_R, B_R, C_R, D_R = sess.run([a, b, A, B, C, D])
print("\na\n", a)
print("\nb\n", b)
print("\na*b\n", A_R)
print("\n2*a*b\n", B_R)
print("\na/b\n", C_R)
print("\na%b\n", D_R)
sess.close()

