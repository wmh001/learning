# -*- coding: utf-8 -*-
"""
Created on Sun Sep 27 22:19:12 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt 
# 字符串
# 字符串用''或""包含
a='Hello World!'
print(a)
# '可以用""包含
print("Let's go!")
# \'与\"在字符串中表示'和"
print('Let\'s go!')
# 字符串不能加数字
# a='123'
# b=a+1
# print(b)
# 类型转换
a='123'
b=int(a)+1
print(b)
pie='3.141592653589'
c=float(pie)+1
print(c)
d=str(3)
print("poisson distribution for $\\mu$ = "+d)
# 带小数点字符串不能直接转换为整数
# d=int(a)+int(pie)
# print(d)
e=int(a)+int(float(pie))
print(e)
# +字符串拼接
print('Hello world!'+' '+'I am Python')
# .format()格式化
print("The value of pi is approximately "+str(np.pi))
# :后未格式化命令，.5f表示保留五位小数的浮点数
print("The value of {} is approximately {:.5f}".format('pi', np.pi))
# 1:d表示第一个条目且表示为十进制。0:表示第零个条目。:b为二进制，:o为八进制，:x为十六进制
# .format()格式化并创建新变量
f="{1:d} plus {0:d} is {2:d}"
print(f.format(2,4,2+4))
print(f)
# 不一定使用参数的全部条目
print("Every {2} has its {3}".format('dog','day','rose','thorn'))
# 使用列表的一个元素。0[2]表示第二个元素，:g表示通用格式（适当时采用科学计数法，浮点数去除末位的0）
print("The thrid element of the list is {0[2]:g}.".format(np.arange(10)))
# %格式化
print("The value of pi is approximately "+str(np.pi))
# s表示字符串，.5f表示保留五位小数的浮点数
print("The value of %s is approximately %.5f"%('pi',np.pi))
# d表示十进制
g="%d plus %d is %d"
# %格式化并创建新变量
print(g%(2,4,2+4))
print(g)

