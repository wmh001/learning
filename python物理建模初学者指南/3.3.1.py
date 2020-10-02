# -*- coding: utf-8 -*-
"""
Created on Fri Oct  2 10:31:08 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
num_points = 10
x_min, x_max = 0, 4
x_values = np.linspace(x_min, x_max, num_points)
y_values = x_values**2
# 检查数组长度是否相同
# x_values=np.linspace(x_min,x_max,num_points+1)
assert len(x_values) == len(y_values),\
    "Length-mismatch: {:d} versus {:d}".format(len(x_values), len(y_values))
# plt.plot(数组 x值数组,数组 y值数组)绘制折线图(蓝色，实线，不标识)
# plt.plot(数组 x值数组,数组 y值数组,str 绘图选项)绘制折线图(
# 红色'r'，蓝色'b'，黑色'k'，绿色'g'
# 用点线连接数据点':'，用虚线连接数据点'--'，用实线连接数据点'-'
# 用小点标识数据点'.'，用圆标识数据点'o'，)
# 各种绘图选项可以组合使用，标识写明而连接不写明的不连接，其余不写明的按默认
# 绘制xy坐标平面
# 从第一个参数中取一个数，从第二个参数中取一个数，组成坐标(x值数组与y值数组长度相同)
plt.plot(x_values, y_values, 'r--o')
# 在图中绘制另一条曲线
y_values = x_values**3
plt.plot(x_values, y_values, '.')
# plt.xlim(int 最小值,int 最大值)，plt.xlim(xmax=最大值,xmin=最小值)，plt.xlim([最小值，最大值])，plt.xlim((最小值，最大值))
# plt.ylim同理，修改x轴y轴显示范围
plt.xlim(1, 6)
plt.ylim([1, 70])
# plt.axis(str 调整方式)，同时调整x轴y轴（
# 曲线刚好填满'tight'、两坐标轴使用同一单位长度'equal'
plt.axis('tight')
plt.axis('equal')
# plt.show()一些python环境用来打开图形窗口
plt.show()
# 对数坐标
# plt.semilogy()垂直取对数坐标,y轴单位长度改变且y轴不在均匀，不改变y的值
plt.semilogy()
# plt.semilogy(参数)在xy平面绘制垂直取对数坐标的新折线图，参数与plt.plot()相同
plt.semilogy(x_values, y_values)
# plt.semilogx()与plt.semilogx(参数)同理
# plt.loglog()xy轴同时取对数
# plt.close()关闭窗口
plt.close()
# 获取数组长度
print(len(x_values))
print(np.shape(x_values))
print(x_values.shape[0])

# np.logspace()创建在对数坐标下等距的数组
# plt.scatter()更精细控制图形细节

# 一些图形后台在脚本结束后仍可以通过IPython修改图形
# 如上例，脚本运行结束后，
"""终端中输入
y_values=x_values**3
plt.plot(x_values,y_values)
可删除旧图形，显示新的图形（默认红色）；"""
"""终端中输入
plt.xlim(1,6)或plt.ylim(1,6)或plt.xlim(xmax=6,xmin=1)或plt.xlim([1,6])或plt.xlim((1,6))或plt.ylim...
可调整x轴、y轴的显示范围为1到6；"""
"""终端中输入
plt.axis('tight')
可调整x轴、y轴显示范围为刚好填满；"""
"""终端中输入
plt.axit('equal')
使2条坐标轴使用同一单位长度"""
"""关闭图形窗口方法：
1）点击窗口右上角叉号
2）IPython输入plt.close()关闭当前窗口,plt.close('all')关闭所有窗口"""
