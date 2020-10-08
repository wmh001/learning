# -*- coding: utf-8 -*-
"""
Created on Thu Oct  8 22:37:52 2020

@author: w'm'h
"""
import numpy as np
import scipy.optimize as so
# 非线性方程的数学求解
# 一般实函数
"""
so.fsolve(函数名 计算函数的名称, int 开始根搜索的数据点, maxfev=int 搜索次数上限, full_output=bool)
so.fsolve(函数名 计算函数的名称, 数组 开始根搜索的数据点组成的数组, maxfev=int 搜索次数上限)
求函数f(x)=0的实数根，函数会从开始根搜索的数据点开始尝试，以节省运算时间
搜索尝试上限默认为400
要获取多少个根，就提供多少数据点
求得的根离数据点最近，如果有多个根其距离最近的根相同，返回多个相同的根，并不合并
返回根的数组
"""


def f(x):
    return x**2 - 1


print(so.fsolve(f, 0.5))
print(so.fsolve(f, -0.5))
print(so.fsolve(f, [-0.5, 0.5]))
print(so.fsolve(f, [-0.5, 0.5, 1.5]))


def g(x):
    return np.sin(x)**10


print(so.fsolve(np.sin, 1))
# 数组误差问题，由于python表示的小数位有限，只能计算出一个近似值
print(so.fsolve(g, 1, maxfev=10000))
# 使用搜索含有奇点函数根时会产生严重错误


def h(x):
    return 1 / (x - 1)


print(so.fsolve(h, 2))
# full_output参数提供更多信息，返回值的同时返回更多信息，信息的最后一句标明了求值正确或求得错误值的一个原因
print(so.fsolve(h, 2, full_output=True))

# 多项式的复数根
# fsolve只求实数根


def J(x):
    return x * (1 + x**3) - 1


print(so.fsolve(J, 1))
print(so.fsolve(J, -1))
"""
np.roots(数组 多项式系数数组)
求多项式函数方程f(x)=0实数根和复数根
多项式系数数组按未知数幂次降序排列
返回值为数组
"""
print(np.roots([1, 0, 0, 1, -1]))
