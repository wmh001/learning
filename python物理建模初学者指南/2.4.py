# -*- coding: utf-8 -*-
"""
Created on Mon Sep 28 22:07:03 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# for循环
b, c = 2, -1
for a in np.arange(-1, 2, 0.3):
    x = (-b + np.sqrt(b**2 - 4 * a * c)) / (2 * a)
    print("a={:.4f},x={:.4f}".format(a, x))
# 一轮循环结束后，循环变量重新赋值
# prthon中代码块只能通过缩进定义
# 缩进只由空格和制表符组成
# 同一代码块必须有一致的缩进
# 嵌套代码块时，缩进量逐层递增
print('')
b, c = 2, -1
for a in np.arange(-1, 2, 0.3):
    x = (-b + np.sqrt(b**2 - 4 * a * c)) / (2 * a)
print("a={:.4f},x={:.4f}".format(a, x))
# 循环体简短时可以在for语句的:之后编写
for i in range(1, 21, 3):
    print(i, i**3)
# while循环
a, b, c = 2, 2, -1
while (b**2 - 4 * a * c >= 0):
    x = (-b + np.sqrt(b**2 - 4 * a * c)) / (2 * a)
    print("a={:.4f},x={:.4f}".format(a, x))
    a = a - 0.3
print("done!")
# 循环长时间运行
for ii in range(10**6):
    if ii % 10**5 == 0:
        print("{:d} percent complete complete ...".format(
            int((100 * ii) / 10**6)))
# 死循环
# while True:
#    print("Here we go again ...")
