# -*- coding: utf-8 -*-
"""
Created on Tue Oct 13 22:52:36 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt
from numpy.random import random as rng


# 随机游走并绘图
def get_trajectory(num_steps):
    x_steps = np.ones(num_steps)
    y_steps = np.ones(num_steps)
    for i in range(0, num_steps):
        if (rng() < 0.5):
            x_steps[i] = -1
        else:
            x_steps[i] = 1
        if (rng() < 0.5):
            y_steps[i] = -1
        else:
            y_steps[i] = 1
    # 累加前k项
    X_steps = np.cumsum(x_steps)
    Y_steps = np.cumsum(y_steps)
    ax = plt.gca()
    ax.set_title("suijiyouzou", size=8, weight='bold')
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    plt.axis('equal')
    plt.plot(X_steps, Y_steps)
    plt.axis('equal')
    x_final = X_steps[-1]
    y_final = Y_steps[-1]
    displacement = np.sqrt(x_final**2 + y_final**2)
    return x_final, y_final, displacement


# 随机游走不绘图
def get_position(num_steps):
    x_steps = np.ones(num_steps)
    y_steps = np.ones(num_steps)
    for i in range(0, num_steps):
        if (rng() < 0.5):
            x_steps[i] = -1
        else:
            x_steps[i] = 1
        if (rng() < 0.5):
            y_steps[i] = -1
        else:
            y_steps[i] = 1
    # 累加前k项
    X_steps = np.cumsum(x_steps)
    Y_steps = np.cumsum(y_steps)
    x_final = X_steps[-1]
    y_final = Y_steps[-1]
    displacement = np.sqrt(x_final**2 + y_final**2)
    return x_final, y_final, displacement


num_steps = 1000
try_times = 4
x = np.zeros(try_times)
y = np.zeros(try_times)
d = np.zeros(try_times)
for i in range(try_times):
    plt.subplot(2, 2, i + 1)
    x[i], y[i], d[i] = get_trajectory(num_steps)

try_times = 400
x = np.zeros(try_times)
y = np.zeros(try_times)
d = np.zeros(try_times)
for i in range(try_times):
    x[i], y[i], d[i] = get_position(num_steps)
plt.figure()
plt.plot(x, y, 'o')
plt.figure()
plt.hist(d**2)
plt.show()
print(np.mean(d))
