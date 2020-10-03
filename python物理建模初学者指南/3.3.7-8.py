# -*- coding: utf-8 -*-
"""
Created on Sat Oct  3 21:33:31 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
# 保存图形为文件
num_points = 26
x_min, x_max = 0, 4
x_values = np.linspace(x_min, x_max, num_points)
y_values = x_values**2
plt.figure()
assert len(x_values) == len(y_values),\
    "Length-mismatch: {:d} versus {:d}".format(len(x_values), len(y_values))
plt.plot(x_values, y_values, label='Population 1')
plt.plot(x_values, x_values**3, label='Population 2')
plt.show()
plt.legend()
ax = plt.gca()
ax.set_title("My first plot", size=24, weight='bold')
ax.set_xlabel("Time [days]")
ax.set_ylabel("Population")
ax.set_xticks(ax.get_xticks())  # 新版bug
ax.set_xticklabels(ax.get_xticks(), family='monospace', fontsize=10)
# 获取支持的文件格式
fig = plt.gcf()
print(fig.canvas.get_supported_filetypes())
"""支持的文件格式：
 'eps': 'Encapsulated Postscript',
 'jpg': 'Joint Photographic Experts Group',
 'jpeg': 'Joint Photographic Experts Group',
 'pdf': 'Portable Document Format',
 'pgf': 'PGF code for LaTeX',
 'png': 'Portable Network Graphics',
 'ps': 'Postscript',
 'raw': 'Raw RGBA bitmap',
 'rgba': 'Raw RGBA bitmap',
 'svg': 'Scalable Vector Graphics',
 'svgz': 'Scalable Vector Graphics',
 'tif': 'Tagged Image File Format',
 'tiff': 'Tagged Image File Format'"""
"""方法一
点击窗口右上角Save键(默认为png格式)"""
# 方法二
# IPython或脚本
# plt.savefig(str 文件名)
plt.savefig("3.3.7.pdf")
matplotlib.rcParams['svg.fonttype'] = 'none'
plt.savefig("3.3.7.svg")
# eps、svg文件可以用Inkscape或Xfig等开源矢量图应用打开并修改
# 但标题、坐标轴标签等文本难以被其他应用编辑
# matplotlib.rcParams['svg.fonttype']='none'或
# matplotlib.rcParams['svg.fonttype']=42将文本以类型形式保存在svg文件中（易于编辑）
