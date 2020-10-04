# -*- coding: utf-8 -*-
"""
Created on Sun Oct  4 18:44:12 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
# 创建窗口并调整大小
plt.figure(figsize=(8, 5))
# 修饰
ax = plt.gca()
ax.set_title("HIVseries", size=24, weight='bold')
ax.set_xlabel("Time [days]")
ax.set_ylabel("Viral Load [copies/ml]")
# 导入实验数据
hiv_data = np.loadtxt(r'python物理建模初学者指南\4.1\HIVseries.csv', delimiter=',')
time = hiv_data[:, 0]
viral_load = hiv_data[:, 1]
assert len(time) == len(viral_load),\
    "Length-mismatch: {:d} versus {:d}".format(len(time), len(viral_load))
plt.plot(time, viral_load, label='Actual data')
# 绘制拟合曲线
# hiv_data[np.shape(hiv_data)[0]为多维数组行数
time = np.linspace(0, hiv_data[np.shape(hiv_data)[0] - 1, 0], 101)
A = -185000
B = 185000
alpha = 30
beta = 0.5
viral_load = A * np.exp(-alpha * time) + B * np.exp(-beta * time)
assert len(time) == len(viral_load),\
    "Length-mismatch: {:d} versus {:d}".format(len(time), len(viral_load))
plt.plot(time, viral_load, label='Fitting')
plt.legend()
plt.show()
