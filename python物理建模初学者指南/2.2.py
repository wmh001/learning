# -*- coding: utf-8 -*-
"""
Created on Thu Sep 24 23:15:50 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# 列表
L = [1, 'a', max, 3 + 4j, 'Hello,world!']
print(L)
# 创建一维数组,参数为正整数
# np.zeros()创建元素为0的数组
a = np.zeros(4)
print(a)
# 创建二维数组，参数为元组
a = np.zeros((3, 5))
print(a)
# np.ones()创建元素为1的数组
a = np.ones((3, 5))
print(a)
# np.eye()创建单位矩阵
a = np.eye(3)
print(a)
# 创建列矩阵
a = np.zeros((3, 1))
print(a)
# 创建三维数组，参数为元组
a = np.zeros((2, 3, 4))
print(a)
# np.size()计算数组尺寸
print(np.size(a))
# np.size(a,b)计算数组a第b行的尺寸
A = np.zeros((2, 5))
print(np.size(A, 1))
# np.shape()计算数组规格
print(np.shape(a))
# np.sum()求元素和
a = np.ones((3, 4))
print(np.sum(a))
# np.mean()求平均值
a = np.eye(3)
print(np.mean(a))
# np.std()计算标准差
a = np.eye(3)
print(np.std(a))
# 列表转化为数组
L = [2.71, 3.14, 3000]
print(np.array(L))
# 列表转化为多维数组
L = [[2.71], [3.14], [3000]]
print(np.array(L))
print(np.array([[2, 3, 5], [7, 11, 13]]))
# np.arange(a,b)创建一维数组a到b-1
print(np.arange(1, 10))
# np.arange(n)创建一维数组n-1
print(np.arange(5))
# np.arange(a,b,n)创建等差数列a到b-n,公差为n
print(np.arange(2.1, 5.4, 0.1))
print(np.arange(0, 10.1, 0.1))
# np.linspace(A,B,N)创建等差数列，首数为A,尾数为B,元素数为N
print(np.linspace(2.1, 5.4, 3))
# 数组连接
a = np.zeros((2, 3))
b = np.ones((2, 3))
# 水平堆叠
h = np.hstack([a, b])
print(h)
# 垂直堆叠
v = np.vstack([a, b])
print(v)
# 根据索引访问数组元素
A = np.array([2, 4, 5])
A[1] = 100
print(A)
# 索引取负值意为倒数
A[-1] = 1000
print(A)
# 访问二维数组元素
A = np.array([[2, 3, 5], [7, 11, 13]])
print(A)
print(A[0])
print(A[0][1])
# 另一种索引模式
print(A[1, 2])
# 修改数组元素
A[1, 2] = 999
print(A)
# 赋值
f = 2.5
g = f
# 浮点数赋值创建新对象
print(g)
f = 3.5
print(g)
# 数组赋值变量绑定到同一对象
A = np.zeros(3)
B = A
A[0] = 1
print(B)
# 数组切片
B = np.array(range(1, 11))
print(B)
# [a:b]从第a个元素到第b-1个元素
print(B[2:5])
# [a:b:c]从第a个元素到第b-1个元素，公差为c
# 最后一个元素为满足a+n*c<b的最大整数
print(B[2:7:2])
print(B[2:8:2])
# 从第零个元素开始，第一个参数可以省略
print(B[:5])
# 到最后一个元素结束，第二个参数可以省略
print(B[5:])
# 多维数组切片
A = np.eye(4)
print(A)
# [a:b:c,d]在第d行从第a个元素到第b-1个元素，公差维c
x = A[1:3:1, 1]
print(x)
# 多维数组分成多个一维数组
A = np.zeros((2, 4))
A[0] = np.array(range(1, 5))
A[1] = np.array(range(5, 9))
print(A)
# 按行分
x = A[0, :]
y = A[1, :]
print(x)
print(y)
# 按列分
h = A[:, 0]
g = A[:, 1]
print(h)
print(g)
# 切片时使用负索引值
print(x[-3:])
# 切片赋值
A = np.zeros(10)
A[1:4] = np.ones(3)
print(A)
# 数组展平
A = np.array([[1, 2], [1, 2]])
print(A)
# .flatten()创建新数组
a = A.flatten()
print(a)
a[1] = 3
print(A)
# np.ravel(A)创建指向同一数据区但形状不同的数据结构
b = np.ravel(A)
print(b)
b[2] = 3
print(A)
# 更改数组形状但不创建新数组
a = np.arange(12)
print(a)
# np.reshape(a,(,))将A改变维元组的形状
b = np.reshape(a, (3, 4))
print(b)
# .reshape(())将调用对象改编为元组的形状
c = b.reshape((2, 6))
print(c)
d = b.reshape((2, 3, 2))
print(d)
print(d)
# 未创建新数组
d[1][1][1] = 12
print(a)
# 以列表和数组未索引
a = np.arange(10, 21)
print(a)
b = [2, 4, 5]
print(a[b])
# 以条件值做索引
a = np.arange(-10, 11)
print(a)
print(a[abs(a) < 5])
