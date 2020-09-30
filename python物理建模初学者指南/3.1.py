# -*- coding: utf-8 -*-
"""
Created on Wed Sep 30 21:33:29 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import urllib.request
# 数据集文件一个对应数组中的一行
# .csv以逗号分隔的数据集文件
# .tsv以制表符或空格分隔的数据集文件
# 未指明分隔方式的文件：.txt、.dat
# 导入数据
# np.loadtxt()读取文本文件数据，默认为.tsv文件，读取.csv文件需指定分隔符。
data_set0 = np.loadtxt(r"python物理建模初学者指南\HIVseries\HIVseries.csv", delimiter=',')
print(data_set0)
""" 注：返回值为数组
       文件名为字符串格式
       分隔符以字符串形式给出
"""
print('first')
# 读取非工作目录的文件
# r表示原始字符串，即反斜线并非转义符
data_file = r"E:\配套代码\Python物理建模初学者指南\PMLSdata\01HIVseries\HIVseries.csv"
data_set1 = np.loadtxt(data_file, delimiter=',')
print(data_set1)
print('second')
# 一处定义多处使用
home_dir = r"E:\配套代码\Python物理建模初学者指南\PMLSdata"
data_dir = home_dir + r"\01HIVseries\HIVseries.csv"
data_set2 = np.loadtxt(data_dir, delimiter=',')
print(data_set2)
# 逐行处理
my_file = open(r"python物理建模初学者指南\HIVseries\HIVseries.csv")
temp_data = []
for line in my_file:
    print(line)
    # 按分隔符分开，分隔符随文件可变
    x, y = line.split(',')
    temp_data += [[float(x), float(y)]]
my_file.close()
print(temp_data)
data_set3 = np.array(temp_data)
print(data_set3)
print('third')
# 导入web数据
web_file = urllib.request.urlopen(
    "http://www.physics.upenn.edu/biophys/"
    + "PMLS/Datasets/01HIVseries/HIVseries.csv")
data_set4 = np.loadtxt(web_file, delimiter=',')
print(data_set4)
