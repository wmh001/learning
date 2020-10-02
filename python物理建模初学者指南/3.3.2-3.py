# -*- coding: utf-8 -*-
"""
Created on Fri Oct  2 21:51:21 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
# 绘制图形
num_points = 26
x_min, x_max = 0, 4
x_values = np.linspace(x_min, x_max, num_points)
y_values = x_values**2
# plt.figure()创建空图形
plt.figure()
assert len(x_values) == len(y_values),\
    "Length-mismatch: {:d} versus {:d}".format(len(x_values), len(y_values))
# plt.plot(数组 x值数组,数组 y值数组,label=曲线名)绘制曲线并创建对应的默认图例
plt.plot(x_values, y_values, label='Population 1')
plt.plot(x_values, x_values**3, label='Population 2')
# plt.legend()左上角显示图例
plt.legend()
# 绘图修改与装饰
# plt.gca()获取坐标轴对象，通过操作该对象的>450中属性操作图形
ax = plt.gca()
# 坐标轴对象.set_title(str 标题名,size=字号,weight=字粗细)添加标题，后两个参数有默认值
# ax.set_title("My first plot")
ax.set_title("My first plot", size=24, weight='bold')
# plt.title与之相同
# plt.title("My first plot",size=24,weight='bold')
# 坐标值标签
# 坐标轴对象.set_xlabel(str x轴标签)设定x轴标签
# 坐标轴对象.set_ylabel
ax.set_xlabel("Time [days]")
ax.set_ylabel("Population")
# 无量纲量单位为[unitless]或[a.u.]
# ax.set_xlabel("speed[$\\mu$m/s]")
# ax.set_ylabel("kinetic energy[J]")
# plt.xlabel，plt.ylabel与之相同
# plt.xlabel("speed[$\\mu$m/s]")
# plt.ylabel("kinetic energy[J]")
# 坐标轴标记字体和大小
# 坐标轴对象.set_xticklabels(坐标轴对象.get_xticks(),family=,fontsize=大小)
ax.set_xticks(ax.get_xticks())  # 新版bug
ax.set_xticklabels(ax.get_xticks(), family='monospace', fontsize=10)
# 坐标轴对象.set_yticklabels同理
# 坐标轴对象.get_lines()获取连线对象，列表索引为曲线系数
lines = ax.get_lines()
# 连线对象[索引].set_label(str 索引名)，在以创建默认图例名的基础上，更改新图例名
"""lines[0].set_label("Infected Population")
lines[1].set_label("Cured Population")
# 坐标轴对象..legend()显示图例
ax.legend()"""
# 连线风格
# plt.setp(连线对象[索引],linestyle=连线形式,linewidth=线宽,color=颜色)
plt.setp(lines[0], linestyle='-', linewidth=3, color='r')
# 坐标轴对象.legend(元组 (曲线1图例名,曲线2图例名,···))在已创建默认图例名的基础上直接设定图例名
ax.legend(("Healthy", "Recovered"))
# plt.errorbar(数组 x值数组,数组 y值数组,yerr=y值误差,xerr=x值误差)绘制带有误差条的图形
# 当后两个参数省略时相当于plt.plot(数组 x值数组,数组 y值数组)
plt.errorbar(x_values, x_values**4, yerr=0.2, xerr=0.2, ecolor='k')
plt.show()
