# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 23:34:24 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# 导出数据
# np.save()将一个数组保存到一个扩展名为.npy的NumPy归档文件（非可读格式）
# np.savez()将多个数组保存到一个扩展名为.npz的NumPy归档文件（非可读格式）
# np.savetxt()将一个数组保存到一个任意扩展名的文本文件（可读格式）
x = np.linspace(0, 1, 1001)
print(x)
y = 3 * np.sin(x)**3 - np.sin(x)
np.save(r'python物理建模初学者指南\HIVseries\x_values', x)
np.save(r'python物理建模初学者指南\HIVseries\y_values', y)
# 生成以制表符为分隔符的.dat文件，如生成,分隔符的文件，需添加参数delimiter=','
np.savetxt(r'python物理建模初学者指南\HIVseries\x_values.dat', x)
np.savetxt(r'python物理建模初学者指南\HIVseries\y_values.dat', y)
np.savez(r'python物理建模初学者指南\HIVseries\xy_values', x_value=x, y_value=y)
# 恢复数据
x2 = np.load(r'python物理建模初学者指南\HIVseries\x_values.npy')
y2 = np.loadtxt(r'python物理建模初学者指南\HIVseries\y_values.dat')
w = np.load(r'python物理建模初学者指南\HIVseries\xy_values.npz')
print(x2)
print(y2)
print(w['x_value'])
print(w['y_value'])
