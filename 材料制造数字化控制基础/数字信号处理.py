# -*- coding: utf-8 -*-

# 导入模块
import numpy as np
import matplotlib.pyplot as plt
# 导入中文字体
from matplotlib.font_manager import FontProperties
font_set = FontProperties(fname=r"c:\windows\fonts\simsun.ttc", size=15)

# 原始数据
T_raw = [25, 50, 80, 110, 150, 190, 310, 300, 360, 430, 520, 800, 770, 870,
         970, 1100, 1150, 1150, 1120, 1080, 1100, 1000, 940, 800, 820, 720,
         800, 560, 480, 420, 380, 360, 300, 310, 280, 250, 230, 250, 190, 175,
         160, 200, 130, 120, 110, 100, 90, 80, 75, 65]
# 将原始数据转化为数组
T_raw = np.array(T_raw)

# 中值滤波（N=5）
# 滤后数据
T_filtered1 = np.zeros(46)
# 窗口滑动
for i in range(46):
    # 计算第i到第i+5个元素的中值
    T_filtered1[i] = np.median(T_raw[i:i+5])
    i = i + 1
x_values = np.arange(5, 51)
# 创建空图形
fig = plt.figure("中值滤波")
# 绘制标题
plt.title("中值滤波", fontproperties=font_set)
# 绘制坐标轴标签
plt.xlabel("t(min)")
plt.ylabel("T(℃)")
# 绘制曲线图
plt.plot(x_values, T_filtered1, 'b-o', markersize=2)
# 一些python环境用来打开图形窗口
plt.show()
print(T_filtered1)

# 基于拉依达准则的奇异数据滤波(L=2)
L = 2
# 滤后数据
T_filtered2 = []
# 横坐标
x_values = []
for i in range(5):
    # 计算算术平均值
    average = np.mean(T_raw[i*10:i*10+10])
    # 计算剩余偏差
    V = T_raw[i*10:i*10+10] - average
    # 计算标准偏差
    sigma = np.sqrt(np.sum(V**2)/9)
    for j in range(10):
        # 判断是否为坏值
        if V[j] <= L * sigma and V[j] >= -L * sigma:
            # 不是坏值的进入数组
            T_filtered2.append(T_raw[i*10+j])
            x_values.append(i * 10 + j + 1)
# 列表转化为数组
T_filtered2 = np.array(T_filtered2)
x_values = np.array(x_values)
# 创建空图形
fig = plt.figure("基于拉依达准则的奇异数据滤波(L=2)")
# 绘制标题
plt.title("基于拉依达准则的奇异数据滤波(L=2)", fontproperties=font_set)
# 绘制坐标轴标签
plt.xlabel("t(min)")
plt.ylabel("T(℃)")
# 绘制曲线图
plt.plot(x_values, T_filtered2, 'b-o', markersize=2)
# 一些python环境用来打开图形窗口
plt.show()
print(T_filtered2)

# 基于拉依达准则的奇异数据滤波(L=3)
L = 3
# 滤后数据
T_filtered2 = []
# 横坐标
x_values = []
for i in range(5):
    # 计算算术平均值
    average = np.mean(T_raw[i*10:i*10+10])
    # 计算剩余偏差
    V = T_raw[i*10:i*10+10] - average
    # 计算标准偏差
    sigma = np.sqrt(np.sum(V**2)/9)
    for j in range(10):
        # 判断是否为坏值
        if V[j] <= L * sigma and V[j] >= -L * sigma:
            # 不是坏值的进入数组
            T_filtered2.append(T_raw[i*10+j])
            x_values.append(i * 10 + j + 1)
# 列表转化为数组
T_filtered2 = np.array(T_filtered2)
x_values = np.array(x_values)
# 创建空图形
fig = plt.figure("基于拉依达准则的奇异数据滤波(L=3)")
# 绘制标题
plt.title("基于拉依达准则的奇异数据滤波(L=3)", fontproperties=font_set)
# 绘制坐标轴标签
plt.xlabel("t(min)")
plt.ylabel("T(℃)")
# 绘制曲线图
plt.plot(x_values, T_filtered2, 'b-o', markersize=2)
# 一些python环境用来打开图形窗口
plt.show()
print(T_filtered2)

# 基于中值数绝对偏差的决策滤波法(L=2)
L = 2
# 滤后数据
T_filtered3 = []
for i in range(10):
    # 计算窗口中值
    Z = np.median(T_raw[i*5:i*5+5])
    # 计算尺度序列
    q = abs(T_raw[i*5:i*5+5] - Z)
    # 计算尺度序列中值
    d = np.median(q)
    Q = 1.4826 * d
    for j in range(5):
        # 判断是否为干扰
        if q[j] < L * Q:
            # ym=xm
            T_filtered3.append(T_raw[i*5+j])
        else:
            # 干扰值用中值代替
            T_filtered3.append(Z)
# 列表转化为数组
T_filtered3 = np.array((T_filtered3))
# 横坐标
x_values = np.arange(1, np.size(T_filtered3) + 1)
# 创建空图形
fig = plt.figure("基于中值数绝对偏差的决策滤波法(L=2)")
# 绘制标题
plt.title("基于中值数绝对偏差的决策滤波法(L=2)", fontproperties=font_set)
# 绘制坐标轴标签
plt.xlabel("t(min)")
plt.ylabel("T(℃)")
# 绘制曲线图
plt.plot(x_values, T_filtered3, 'b-o', markersize=2)
# 一些python环境用来打开图形窗口
plt.show()
print(T_filtered3)

# 基于中值数绝对偏差的决策滤波法(L=3)
L = 3
# 滤后数据
T_filtered3 = []
for i in range(10):
    # 计算窗口中值
    Z = np.median(T_raw[i*5:i*5+5])
    # 计算尺度序列
    q = abs(T_raw[i*5:i*5+5] - Z)
    # 计算尺度序列中值
    d = np.median(q)
    Q = 1.4826 * d
    for j in range(5):
        if q[j] < L * Q:
            # 判断是否为干扰
            T_filtered3.append(T_raw[i*5+j])
        else:
            # 干扰值用中值代替
            T_filtered3.append(Z)
# 列表转化为数组
T_filtered3 = np.array((T_filtered3))
# 横坐标
x_values = np.arange(1, np.size(T_filtered3) + 1)
# 创建空图形
fig = plt.figure("基于中值数绝对偏差的决策滤波法(L=3)")
# 绘制标题
plt.title("基于中值数绝对偏差的决策滤波法(L=3)", fontproperties=font_set)
# 绘制坐标轴标签
plt.xlabel("t(min)")
plt.ylabel("T(℃)")
# 绘制曲线图
plt.plot(x_values, T_filtered3, 'b-o', markersize=2)
# 一些python环境用来打开图形窗口
plt.show()
print(T_filtered3)

# 去极值平均滤波法
T_filtered4 = []
# 窗口滑动
for i in range(46):
    # 去极值并计算平均值，进入数组
    T_filtered4.append((sum(T_raw[i:i+5]) - min(T_raw[i:i+5]) - max(T_raw[i:i+5]))/3)
# 列表转化为数组
T_filtered4 = np.array(T_filtered4)
# 横坐标
x_values = np.arange(5, 51)
# 创建空图形
fig = plt.figure("去极值平均滤波法")
# 绘制标题
plt.title("去极值平均滤波法", fontproperties=font_set)
# 绘制坐标轴标签
plt.xlabel("t(min)")
plt.ylabel("T(℃)")
# 绘制曲线图
plt.plot(x_values, T_filtered4, 'b-o', markersize=2)
# 一些python环境用来打开图形窗口
plt.show()
print(T_filtered4)
