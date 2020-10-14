# -*- coding: utf-8 -*-
"""
Created on Wed Oct 14 22:27:50 2020

@author: w'm'h
"""
import matplotlib.pyplot as plt
# 图像处理
# plt.imread(str 文件名)导入图像，返回数组
Photo = plt.imread(r'python物理建模初学者指南\7.1\bwCat.tif')
# 数组形状
print(Photo.shape)
# 元素类型
print(Photo.dtype)
# 访问元素
print(Photo[:10, :10])
# plt.imshow(数组 图像数组)显示图像
plt.imshow(Photo)
# 修改默认设置
# plt.set_cmap(str 颜色名)设置颜色表
plt.set_cmap('gray')
# 移除坐标轴
plt.axis('off')
# 改变背景颜色
fig = plt.gcf()
fig.set_facecolor('red')
# plt.imsave(str 文件名,数组 图像数组, cmap=str 颜色名)保存图像
plt.imsave(r'python物理建模初学者指南\7.1\cat.jpg', Photo, cmap='gray')
# 操作图像
plt.figure()
new_cat = (Photo < Photo.mean())
plt.imshow(new_cat)
plt.axis('off')
plt.show()
