# -*- coding: utf-8 -*-
"""
Created on Tue Oct  6 23:06:04 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt 
from numpy.random import random as rng
data=rng(1000)
plt.figure()
"""
plt.hist(数组, 缺省参数列表)
1）检查义列数据并确定其中数据的范围
2）将一列数据分割为一系列等距的分组
3）以一系列数据条表示结果
4）返回值为一个元组，元组中包含了两个数组，以及一个名为“<a list of 10 Patch objects>”的条目
缺省参数：bins=int m 生成m个等距的数据条
        align=str s s='mid'指定每个数据条的中心值默认使用每个分组的中心点
"""
# 5plt.hist(data)
"""
plt.hist(data, bins = 1)
plt.hist(data, bins = 10)
plt.hist(data, bins = 100)
plt.hist(data, bins = 1000)
"""
# 获取返回值（每组频数和分组区间点）
counts, bin_edges, _ = plt.hist(data)
print(counts)
print(bin_edges)
# 只获取每组频数和分组区间点，不作图
counts, bin_edges = np.histogram(data)
print(counts)
print(bin_edges)
# plt.bar(数组 左边缘坐标, 数组 每组频数, width = 条形图宽度, color = str or str列表)
# 绘制自定义数据条
# 当color = str列表时，列表中的颜色依次使用
plt.figure()
# 计算组距
bin_size = bin_edges[1] - bin_edges[0]
# 宽度与高度成正比
new_widths = bin_size * counts / counts.max()
plt.bar(bin_edges[:-1], counts, width = new_widths, color = ['r', 'g', 'b'])
