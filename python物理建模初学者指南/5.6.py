# -*- coding: utf-8 -*-
"""
Created on Thu Oct  8 23:45:41 2020

@author: w'm'h
"""
import numpy as np
# 求解线性等式
import scipy.linalg as sla
"""
sla.inv 矩阵的逆
sla.det 行列式
sla.sqrtm 矩阵的平方根
sla.expm 矩阵指数
sla.eig 矩阵的特征值和特征向量
sla.eigh 埃尔米特矩阵的特征值和特征向量
sla.svd 奇异值分解
"""
c = np.array([[1, 3], [3, 4]])
print(c)
print(sla.inv(c))
print(np.dot(sla.inv(c), c))

"""
求[a1 a2]T=[[c11 c12] [x1 x2]T 的解
           [c21 c22]]
x=c^(-1)·a
"""
