# -*- coding: utf-8 -*-
"""
Created on Thu Oct 15 22:17:13 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt 
from matplotlib import animation
from numpy.random import random as rand

# 随机动画
# 定义步数
num_steps = 100

plt.close('all')
# 定义坐标轴范围
bound = 20
fig = plt.figure()
ax = plt.axes(xlim=(-bound, bound), ylim=(-bound, bound))

(my_line,) = ax.plot([], [], lw=2)
(my_point,) = ax.plot([], [], 'ro', ms=9)
# 取随机数并累加
x_steps = 2 * (rand(num_steps) < 0.5) - 1
y_steps = 2 * (rand(num_steps) < 0.5) - 1
x_coordinate = x_steps.cumsum()
y_coordinate = y_steps.cumsum()
# 定义更新函数
def get_step(n, x, y, this_line, this_point):
    this_line.set_data(x[:n + 1], y[:n + 1])
    this_point.set_data(x[n], y[n])
# animation.FuncAnimation(图像名称, 函数 更新函数, frames=int 帧数, fargs=(x坐标, y坐标, 线对象, 点对象))
# 生成动画
my_movie = animation.FuncAnimation(fig, get_step, frames=num_steps,
                                   fargs=(x_coordinate, y_coordinate, my_line, my_point))

