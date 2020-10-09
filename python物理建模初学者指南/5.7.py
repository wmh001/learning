# -*- coding: utf-8 -*-
"""
Created on Fri Oct  9 22:19:58 2020

@author: w'm'h
"""
import numpy as np
import matplotlib.pyplot as plt

# 单变量函数值积分
import scipy.integrate as si
"""
si.quad(函数 预定义函数名, 积分下限, 积分上限, limit=int 细分数)对预定义函数积分
细分数有缺省值50
返回积分结果和误差估计值
"""
x_max = np.linspace(0, 3 * np.pi, 12)
print(x_max)
integral = np.zeros(x_max.size)
for i in range(x_max.size):
    integral[i], error = si.quad(np.cos, 0, x_max[i])
print(integral)
plt.plot(x_max, integral)
plt.show()


# 对自定义函数积分
def f(x):
    return x**2


print(si.quad(f, 0, 2)[0])

# 对震荡函数积分
# 对高速震荡函数做积分时，如果使用默认的设置，将无法收敛
# 解决方法：增加细分数
# print(si.quad(np.cos, 0, 5000)[0])
print(si.quad(np.cos, 0, 5000, limit=1000)[0])
print(np.sin(5000))


# 参数依赖性
def g(x, a, b, c):
    return a * x**2 + b * x + c


# g对(a,b,c)=(1,2,3)积分
# 方法一定义虚函数
def h(x):
    return g(x, 1, 2, 3)


print(si.quad(h, -1, 1)[0])
# 方法二使用关键字参数和参数值，仅适用于函数的第一个参数是积分变量的情况
print(si.quad(g, -1, 1, args=(1, 2, 3))[0])
