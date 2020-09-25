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
print(B[2:7:2])
print(B[2:8:2])
# 从第零个元素开始，第一个参数可以省略
print(B[:5])
# 到最后一个元素结束，第二个参数可以省略
print(B[5:])
