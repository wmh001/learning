# -*- coding: utf-8 -*-
"""
Created on Mon Oct 12 22:12:51 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# 向量场和流线图

# 向量场
"""
plt.quiver(数组 网格数组1, 数组 网格数组2, 数组 , 数组)
绘制二维向量场
后两个数组指定了对应(x,y)坐标处的二维向量
"""
coords = np.linspace(-1, 1, 11)
X, Y = np.meshgrid(coords, coords)
Vx, Vy = Y, -X
plt.quiver(X, Y, Vx, Vy)
plt.figure()
# 显示钟形曲面z=e^(-x^2-y^2)在等势线绘图上的梯度
coords = np.linspace(-2, 2, 101)
# 生成网格数组，每五个点
X, Y = np.meshgrid(coords[::5], coords[::5])
# 生成函数值数组
R = np.sqrt(X**2 + Y**2)
Z = np.exp(-R**2)
# 生成网格数组，不间隔点
x, y = np.meshgrid(coords, coords)
r = np.sqrt(x**2 + y**2)
z = np.exp(-r**2)
ds = coords[5] - coords[0]
# 估计网格上的求值函数梯度
dX, dY = np.gradient(Z, ds)
# 绘制填充等势线
plt.contourf(x, y, z, 25)
# 设置颜色
plt.set_cmap('coolwarm')
# 绘制向量场
plt.quiver(X, Y, dX.transpose(), dY.transpose(), scale=25, color='k')
# 绘制曲面z=e^(-x^2-y^2)
fig = plt.figure()
ax = Axes3D(fig)
ax.plot_surface(x, y, z)

# 流型
fig = plt.figure()
lower = -2
upper = 2
step = 0.2
coords = np.arange(lower, upper + step, step)
X, Y = np.meshgrid(coords, coords)
Vx, Vy = Y, -X
plt.streamplot(X, Y, Vx, Vy, linewidth=2)
plt.show()
