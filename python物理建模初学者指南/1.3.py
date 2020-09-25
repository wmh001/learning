# -*- coding: utf-8 -*-
"""
Created on Thu Sep 24 23:05:28 2020

@author: w'm'h (python3.8)
"""
# 导入模块
import numpy
print(numpy.sqrt(2))
# 导入模块且调用时省略模块名
from numpy import *
print(sqrt(2))
# 导入模块且取别名
import numpy as np
print(np.sqrt(2))
# 导入特定函数
from numpy import exp
print(exp(3))
# 导入函数且取别名
from numpy.random import random as rng
print(rng())
