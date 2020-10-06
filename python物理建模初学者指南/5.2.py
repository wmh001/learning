# -*- coding: utf-8 -*-
"""
Created on Tue Oct  6 00:19:34 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt

# 随机数和模拟

# 模拟抛硬币
from numpy.random import random as rng
samples = np.zeros(100)
for i in range(0, 100):
    samples[i] = rng()
flips = (samples < 0.5)
print(np.sum(flips))


# 布朗运动轨迹线
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
    plt.figure()
    ax = plt.gca()
    ax.set_title("bulangyundong", size=24, weight='bold')
    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    plt.axis('equal')
    plt.plot(X_steps, Y_steps)
    plt.show()


get_trajectory(500)
