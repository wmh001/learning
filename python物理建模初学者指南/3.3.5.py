# -*- coding: utf-8 -*-
"""
Created on Sat Oct  3 15:17:15 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
# 同一坐标轴上的多重绘图
x = np.linspace(0, 1, 51)
"""方法一
y1=np.exp(x)
y2=x**2
plt.plot(x,y1,'r')
plt.plot(x,y2,'ko')"""
"""方法二
y1=np.exp(x)
y2=x**2
# plt.plot(曲线一参数,曲线二参数,···)同坐标轴下绘制多条曲线
# plt.plot(x,y1,x,y2)
plt.plot(x,y1,'r',x,y2,'ko')"""
# 方法三
# plt.plot(数组 x值数组,二维数组 y值二位数组,str 绘图选项)每个x值与对应一列y值绘制一条曲线
# 两曲线绘图选项或按默认或必须相同
num_curves = 2
y = np.zeros((x.size, num_curves))
y[:, 0] = np.exp(x)
y[:, 1] = x**2
plt.plot(x, y, 'ro')
# 替换曲线
# 方法一
# plt.cla()清除坐标轴
plt.cla()
# 绘制新图形
num_curves = 3
y = np.zeros((x.size, num_curves))
for n in range(num_curves):
    y[:, n] = np.sin((n + 1) * x * 2 * np.pi)
plt.plot(x, y)
plt.show()
"""# 方法二（matplotlib3已弃用hold()
# Axes的hold方法
# 获取坐标轴对象
ax=plt.gca()
ax.hold(False)
t=np.linspace(0,5*np.pi,501)
plt.plot(t,np.sin(t),'g--')"""
# 多重窗口
# plt.figure(窗口名)创建新窗口，并停止修改之前的窗口，之后脚本或命令行仅操作该窗口
# 当窗口名省略时，使用之前窗口的下一个数字（第一个窗口位1，第二个窗口为2，类推）命名，并停止修改之前的窗口，之后脚本或命令行仅操作该窗口
# 当窗口名为新名字时，将创建以此为名的新窗口，并停止修改之前的窗口，之后脚本或命令行仅操作该窗口
# 当窗口为已存在名字时，停止修改之前的窗口，脚本或命令行再次操作该窗口
# plt.figure(1)
# 绘制新窗口Figure 2
fig = plt.figure()
ax = Axes3D(fig)
t = np.linspace(0, 5 * np.pi, 501)
ax.plot(np.cos(t), np.sin(t), t)
plt.show()
# 绘制新窗口Joe
plt.figure('Joe')
num_curves = 2
y = np.zeros((x.size, num_curves))
y[:, 0] = np.exp(x)
y[:, 1] = x**2
plt.plot(x, y, 'ro')
plt.show()
# 返回窗口Figure 1并修饰
plt.figure(1)
ax = plt.gca()
ax.set_title("My first plot", size=24, weight='bold')
# 返回窗口Joe并修饰
plt.figure('Joe')
ax = plt.gca()
ax.set_title("My third plot", size=24, weight='bold')
