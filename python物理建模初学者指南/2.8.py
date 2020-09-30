# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 16:40:11 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# 嵌套
rows = 3
columns = 4
A = np.zeros((rows, columns))
print(A)
for i in range(rows):
    for k in range(columns):
        A[i, k] = i**2 + k**3
print(A)
