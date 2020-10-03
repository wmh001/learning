# -*- coding: utf-8 -*-
"""
Created on Sat Oct  3 21:01:58 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
from numpy.random import random
# 子绘图
# 多图形居于一个窗口中
t = np.linspace(0, 1, 101)
plt.figure()
# plt.subplot(M,N,p)将当前窗口按M行N列的网格分隔为多个子区域，并设置第p（1<=p<=M*N）个子区域为激活的（之后操作仅针对激活的）
# 之后操作可以分行编写，也可以在同一行编写，用;分隔
# 左上
plt.subplot(2, 2, 1)
# 绘制直方图
plt.hist(random(20))
# 右上
plt.subplot(2, 2, 2)
plt.plot(t, t**2, t**3 - t)
# 左下
plt.subplot(2, 2, 3)
plt.plot(random(20), random(20), 'r*')
# 右下
plt.subplot(2, 2, 4)
plt.plot(t * np.cos(10 * t), t * np.sin(10 * t))
plt.show()
# plt.tight_layout()处理子绘图错位
# 当M或N的值关闭时，现有子绘图将被清除
