# -*- coding: utf-8 -*-
"""
Created on Sun Oct  4 23:33:40 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# 自定义函数
"""
def 函数名(参数列表):
    \"""
    文档字符串
    用做函数的help显示信息
    \"""
    函数体
    return 返回值
"""


def taxicab(pointA, pointB):
    """
    计算出租车距离。
        pointA = (x1, y1)
        pointB = (x2, y2)
    returns |x2-x1| + |y2-y1|
    """
    interval = abs(pointB[0] - pointA[0]) + abs(pointB[1] - pointA[1])
    return interval


fare_rate = 0.40
start = (1, 2)
stop = (4, 5)
trip_cost = taxicab(start, stop) * fare_rate
print(trip_cost)
"""
函数执行后，将丢弃所有函数中本地变量
在IPython中，执行函数保存的文件，之后可在IPython中调用该函数
模块是一个包含了一系列定义和赋值的脚本，可以import
模块名.函数名 表示该模块中定义的该函数，可以import
使用自定义模块时，应将模块定义文件与主脚本置于同一目录中
"""
"""
更新函数
对于脚本中定义的函数，使用Run按键或%run命令运行脚本
定义已导入模块中的函数，1）重启Spyder
                    2)reload函数
                    from imp import reload
                    reload(模块名)
"""


# 参数、关键字和缺省值
def distance(pointA, pointB=(0, 0), metric='taxi'):
    """
    计算出租车距离或乌鸦飞行距离。
        pointA = (x1, y1) 或 [x1, y1] 或 np数组
        pointB = (x2, y2) 或 [x2, y2] 或 np数组 默认 (0, 0)
    metric = str 默认 'taxi'
    metric == 'taxi' 时，returns |x2-x1| + |y2-y1|
    否则，returns sqrt( (x2-x1)**2 + (y2-y1)**2 )
    """
    if metric == 'taxi':
        interval = abs(pointB[0] - pointA[0]) + abs(pointB[1] - pointA[1])
    else:
        interval = np.sqrt((pointB[0] - pointA[0])**2 +
                           (pointB[1] - pointA[1])**2)
    return interval


# 省略后两个参数
print(distance((3, 4)))
# 省略后一个参数
print(distance((3, 4), (1, 2)))
# 不省略参数
print(distance((3, 4), (1, 2), 'normal'))
# 参数列表必须按顺序排列，被省略的参数位于参数列表后几位
# print(distance((3,4),'euclid'))
# 要打乱顺序或省略中间参数，必须指明参数名
print(distance(pointB=(1, 2), metric='normal', pointA=(3, 4)))
print(distance(metric='normal', pointA=(3, 4)))
# 返回值
"""
函数对于接受参数的数量和类型没有限制
函数的返回值是一个对象，未指定返回值时返回None对象
"""


# 旋转二维数组
def rotate_vector(vector, angle):
    """
    根据所给角度旋转二维数组。
        vector = (x, y) 或 [x,y] 或 np数组
        angle = int 或 float 以弧度表示的旋转角度（逆时针为正）
    returns 旋转后的二维数组（以np数组的形式）
    """
    ratotion_matrix = np.array([[np.cos(angle), -np.sin(angle)],
                                [np.sin(angle), np.cos(angle)]])
    return np.dot(ratotion_matrix, vector)


vec = [1, 1]
theta = np.pi / 2
r = rotate_vector(vec, theta)
print(r)
# 分解可迭代对象（元组、列表、字符串和数字）
x, y = r
print(x)
print(y)
# _表示虚拟变量，其值不能显示在变量管理器中
_, z = r
print(_)
print(z)
# 分解为元素和列表（并非np数组）
first, *rest = r
print(first)
print(rest)
t = np.linspace(0, 5, 6)
first, *rest = t
print(first)
print(rest)
*rest, last = t
print(rest)
print(last)
"""
自定义函数参考原则：
1）只通过函数的参数向函数传递数据
2）不要修改函数的参数
3）使用return返回计算结果
原因：避免除返回值外对计算机状态的任何影响
（如在数组作为参数时，并不会自动生成数组的拷贝，因此函数中对数组的修改将影响函数外。
一方面，这节省了数组拷贝的时间；另一方面，增加了调试难度。对于小型数组，在函数中修改数组得不偿失）
"""


def running_average(x):
    """
    计算数组前i个数的平均值。
        x = 数组
    returns 生成的新数组
    """
    # 创建空数组
    y = np.zeros(len(x))
    current_sum = 0.0
    # 插值
    for i in range(len(x)):
        current_sum += x[i]
        y[i] = current_sum / (i + 1.0)
    return y


print(np.arange(11))
print(running_average(np.arange(11)))
