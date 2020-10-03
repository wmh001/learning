# -*- coding: utf-8 -*-
"""
Created on Sat Oct  3 12:07:02 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
# 3D图形
from mpl_toolkits.mplot3d import Axes3D
# 绘制螺旋线
# 创建空窗口
fig = plt.figure()
# Axes3D(图形对象)创建关联在图形上的3D对象
ax = Axes3D(fig)
# 生成数组
t = np.linspace(0, 5 * np.pi, 501)
# 3D对象.plot(数组 x值数组,数组 y值数组,数组 z值数组)绘制曲线
ax.plot(np.cos(t), np.sin(t), t)
# 3D对象.view_init(elev=z轴仰角,azim=(x，y)平面的方位角)指定视角，角采用角度制
ax.view_init(elev=0, azim=30)
# 部分图形后台支持拖拽改变视角
plt.show()
