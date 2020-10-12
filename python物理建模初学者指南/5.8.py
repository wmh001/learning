# -*- coding: utf-8 -*-
"""
Created on Sat Oct 10 23:13:51 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt
# 微分方程的数值解
from scipy.integrate import odeint
"""
1）问题重构
如d2y/dx2=-y+g(t)
由于odeint只能求解dy/dt=F(y,t)形式的微分方程，y是有2个条目得数组，F(y,t)返回一个具有两个条目得数组
F(y,t)=[y2
        -y1+g]
设y1=y,y2=dy1/dt
得dy1/dt=y2
dy2/dt=-y1+g
"""


# 2）ODE求解
# odeint(函数 函数名, 一维数组 初始值数组y0, 一维数组 在何处计算y的值t)
# 返回一维数组y元素为y在指定点的值
# 数组t的第一个条目是应用初始值y0的时间
def F(y, t):
    dy = [0, 0]
    dy[0] = y[1]
    dy[1] = -y[0]
    return dy


t_min = 0
t_max = 10
dt = 0.1
t = np.arange(t_min, t_max, dt)
initial_condition = [(1.0, 0.0), (0.0, 1.0)]
plt.figure()
for y0 in initial_condition:
    y = odeint(F, y0, t)
    plt.plot(t, y[:, 0], linewidth=2)

skip = 5
t_test = t[::skip]
plt.plot(t_test, np.cos(t_test), 'bo')
plt.plot(t_test, np.sin(t_test), 'go')
plt.show()
