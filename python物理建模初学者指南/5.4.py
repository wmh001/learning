# -*- coding: utf-8 -*-
"""
Created on Wed Oct  7 22:19:10 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# 等势线绘图和曲面
# 生成绘图点网格
x_vals = np.linspace(-3, 3, 21)
y_vals = np.linspace(0, 10, 11)
# np.meshgrid(一维数组 数组1,一维数组 数组2)
# 设数组1有N个条目，数组2有M个条目，
# 函数将返回两个均为N*M个条目的数字，分别包含每个网格点的x和y坐标
# 返回数组1[x][y]=数组1[y]，返回数组2[x][y]=数组2[x]
X, Y = np.meshgrid(x_vals, y_vals)
print(x_vals)
print(y_vals)
print(X)
print(Y)
# 等势线绘图
"""
plt.contour(数组 网格数组1, 数组 网格数组2, 数组 函数值数组, int 等势线条数, linewidths=int 线宽度, colors=str 颜色)
绘制等势图（等势线位置均分）
返回值为ContourSet对象
等势线条数、线宽度、颜色有缺省值
plt.contour(数组 网格数组1, 数组 网格数组2, 数组 函数值数组, 数组 等势线高度数组, linewidths=int 线宽度, colors=str 颜色)
绘制等势图（等势线位置依次取等势线数组元素）
返回值为ContourSet对象
线宽度、颜色有缺省值
数组缺失调用第一个数组
"""
# 对z(x,y)=cosx,siny进行可视化，默认条数为10条
Z = np.cos(X) * np.sin(Y)
plt.contour(X, Y, Z)
plt.figure()
cs = plt.contour(X, Y, Z, 10, linewidths=3, colors='k')
# plt.clabel(ContourSet对象, fontsize=字号)添加标签信息
plt.clabel(cs, fontsize=10)
"""
plt.contour(数组 网格数组1, 数组 网格数组2, 数组 函数值数组, cmap=颜色映射)
绘制等势图（等势线位置均分），相邻等势线间填充颜色
cmap有缺省值help(plt.cm)
"""
plt.figure()
plt.contourf(X, Y, Z, cmap=plt.cm.hot)
# plt.set_cmap改变pyplot使用的颜色集
plt.set_cmap(plt.cm.hot)

# 曲面绘图
# Axes3D(图形对象)创建关联在图形上的3D对象
ax = Axes3D(plt.figure())
"""
3D对象.plot_surface(数组 网格数组1, 数组 网格数组2, 数组 函数值数组, rstride=行步幅, cstride=列步幅, cmap=颜色映射)
绘制3维绘图
行步幅、列步幅有缺省值
创建3维绘图会占用大量的计算资源，因此python在生成曲面时会尽量减少所使用的数据点。
默认使用提供数据点的1/10，方法时每次跳过10行10列选取一个数据点（行步幅维10，列步幅维10）
默认使用单一颜色
默认一个假象光源
"""
ax.plot_surface(X, Y, Z, rstride=1, cstride=1)

ax0 = Axes3D(plt.figure())
ax0.plot_surface(X, Y, Z, rstride=1, cstride=1, cmap=plt.cm.gray)
plt.show()
