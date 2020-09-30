# -*- coding: utf-8 -*-
"""
Created on Tue Sep 29 22:47:28 2020

@author: w'm'h (python3.8)
"""
import numpy as np
"""符号内
注释"""
# 行内注释
# %edit打开editor窗格
# %edit 文件名(.py) 用默认文本编辑器打开文件
# %run 文件名(.py) 运行python脚本
# 黄色三角形 可能发生错误
# 红色圆形 无法运行
# python遇上第一个错误就退出
# NameError 拼写错误
# numpy提供的警告
# 不停止运行
for x in np.arange(-1, 8):
    print(x, np.log(x))
# 代码划分，Run Cell分块执行
# %%
# 错误抛出
# 出现错误停止运行
for x in np.arange(-1, 8):
    assert (x > 0), "I do not know how to take the log of {}".format(x)
    print(x, np.log(x))
# 给参数常量命名
# 头注释中写明单位

# %%
