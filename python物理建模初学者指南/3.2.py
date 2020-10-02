# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 23:34:24 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# 导出数据
x = np.linspace(0, 1, 1001)
print(x)
y = 3 * np.sin(x)**3 - np.sin(x)
# np.save(str npy文件名,数组 数组名)将一个数组保存到一个扩展名为npy的NumPy归档文件（非可读格式）
np.save(r'python物理建模初学者指南\HIVseries\x_values', x)
np.save(r'python物理建模初学者指南\HIVseries\y_values', y)
# np.savetxt(str 文件名,数组 数组名)将一个数组保存到一个任意扩展名的文本文件（可读格式），以制表符分隔
# np.savetxt(str 文件名,数组 数组名,delimiter=',')将一个数组保存到一个任意扩展名的文本文件（可读格式），以,分隔
np.savetxt(r'python物理建模初学者指南\HIVseries\x_values.dat', x)
np.savetxt(r'python物理建模初学者指南\HIVseries\y_values.dat', y)
# np.savez(str npz文件名,键名=数组名,键名=数组名)将多个数组保存到一个扩展名为.npz的NumPy归档文件（非可读格式）
np.savez(r'python物理建模初学者指南\HIVseries\xy_values', x_value=x, y_value=y)
# np.load(str npy或npz文件名)恢复数据
# np.loadtxt(str dat文件名)恢复数据
x2 = np.load(r'python物理建模初学者指南\HIVseries\x_values.npy')
y2 = np.loadtxt(r'python物理建模初学者指南\HIVseries\y_values.dat')
w = np.load(r'python物理建模初学者指南\HIVseries\xy_values.npz')
print(x2)
print(y2)
print(w['x_value'])
print(w['y_value'])
# file.open(str 文件名,str 打开方式)打开文件，若有同名文件将删除，打开方式：'w'以可写方式打开
my_file = open(r'python物理建模初学者指南\HIVseries\power.txt', 'w')
print(" N  \t\t2**N\t\t3**N")
print("--- \t\t----\t\t----")
# file.write(str 数据)写入文件，需换行处必须加\n
my_file.write("N \t\t2**N\t\t3**N\n")
my_file.write("---\t\t----\t\t----\n")
# %%
for N in range(11):
    print(" {:d}  \t\t {:d}  \t\t{:d}".format(N, pow(2, N), pow(3, N)))
    my_file.write("{:d}\t\t{:d}\t\t{:d}\n".format(N, pow(2, N), pow(3, N)))
# file.close()关闭文件
my_file.close()
