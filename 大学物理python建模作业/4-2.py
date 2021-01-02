# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import math
import scipy.integrate as si

# 参数设置
# 真空介电常数常数，单位：C^2/N*m^2
epsilon0 = 8.85418782 / 1000000000000
# 线电荷密度，单位：C/m
Lambda = -1
# 导线与垂足的距离，单位：m
d = 1

# 初始化网格
x_vals = np.linspace(-5.5, 5.5, 101)
y_vals = np.linspace(-5.5, 5.5, 101)
X, Y = np.meshgrid(x_vals, y_vals)
# 点与垂足的距离，单位：m
D = np.sqrt(X * X + Y * Y)
# 电场大小，单位：N/C
integral = np.zeros(np.shape(D))
# 面电荷密度，单位：C/m^2
sigma = np.zeros(np.shape(D))

# 创建关联在图形上的3D对象
ax = Axes3D(plt.figure())
# 设置坐标值标签
ax.set_xlabel("x(m)")
ax.set_ylabel("y(m)")
ax.set_zlabel("σ(C/m^2)")


# 计算导线上一点在平面上一点产生的电场强度
def dE(l, D):
    return -Lambda * l / (4 * epsilon0 * math.pi * (l * l + D * D) * np.sqrt(
        (l * l + D * D)))


# 计算整条导线在平面上一点产生的电场强度
def E(D):
    return si.quad(dE, d, float('inf'), args=D)[0]


# 逐点计算面电荷密度
for i in range(np.shape(D)[0]):
    for j in range(np.shape(D)[1]):
        integral[i][j] = E(D[i][j])
        sigma[i][j] = 2 * epsilon0 * integral[i][j]

# 设置Z轴范围
ax.set_zlim(0, 0.20)
# 绘制曲面图
ax.plot_surface(X, Y, sigma, rstride=1, cstride=1, cmap="rainbow")
plt.show()
