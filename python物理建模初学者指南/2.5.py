# -*- coding: utf-8 -*-
"""
Created on Mon Sep 28 22:38:03 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# 矢量化数学
# 在整个数组上执行操作，而非一个数字
# 输出列表
b, c = 2, -1
a = np.arange(-1, 2, 0.3)
print((-b + np.sqrt(b**2 - 4 * a * c)) / (2 * a))
# 矢量化运算比for循环更快
# 原生列表
x = [1, 2, 3, 4, 5, 6]
# 2*list表示2个list合并位同一列表
print(2 * x)
# 未定义列表加整数
# print(x+2)
# 未定义列表乘列表
# print(x*x)
# 未定义列表键列表
# print(x-x)
# 数组
y = np.arange(1, 7)
# 生成原数组中的每个元素乘2的数组
print(2 * y)
# 生成原数组中的每个元素加2的数组
print(y + 2)
# 生成原数组中的每个元素平方的数组
print(y * y)
# 生成原数组中的每个元素自减的数组
print(y - y)
# 形状相同的多维数组的逐项操作
a = np.eye(3)
b = np.ones((3, 3))
if a.shape == b.shape:
    print(a + b)
    print(a * b)
# 点积
a = np.array([1, 2, 3])
b = np.array([1, 0.1, 0.01])
print(a, b)
print(a * b)
print(np.dot(a, b))
# 数组化简
a = np.vstack((np.arange(10), np.arange(1, 11)))
print(a)
# np.sum(a,n)计算数组a的元素a[m0][m1]...[mn]...的除了第n个索引[mn]不同
# 其他索引都相同的所有元素之和组成的数组
# 计算各列元素之和
# a[0][n]+a[1][n],n取0、1、2、...、9组成的数组
print(np.sum(a, 0))
# 计算各行元素之和
# a[n][0]+a[n][1]+...+a[n][10],n取0、1组成的数组
print(np.sum(a, 1))
# 计算各元素之和
print(np.sum(a))
# 使用python内建.sum()函数
print(a.sum(0))
print(a.sum(1))
print(a.sum())
# np.prod()求积
print(np.prod(a, 0))
print(np.prod(a, 1))
print(np.prod(a))
# np.mean()求平均值
print(np.mean(a, 0))
print(np.mean(a, 1))
print(np.mean(a))
# np.std()求标准差
print(np.std(a, 0))
print(np.std(a, 1))
print(np.std(a))
# np.min()求最小值
print(np.min(a, 0))
print(np.min(a, 1))
print(np.min(a))
# np.max()求最大值
print(np.max(a, 0))
print(np.max(a, 1))
print(np.max(a))
