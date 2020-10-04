# -*- coding: utf-8 -*-
"""
Created on Sun Oct  4 21:52:30 2020

@author: w'm'h (python3.8)
"""
import numpy as np
import matplotlib.pyplot as plt
#
# 创建窗口
plt.figure()
# 修饰
ax = plt.gca()
ax.set_title("novick", size=24, weight='bold')
ax.set_xlabel("Time [hours]")
ax.set_ylabel("Fraction of maximum beta-galactosidase activity")
"""# x轴y轴取相同单位长度
ax.set_aspect(1./ax.get_data_ratio())"""
A = 1
tao = 1
t = np.linspace(1, 2, 101)
wt = A * (np.exp(-t / tao) - 1 + 1 / tao)
assert len(t) == len(wt),\
    "Length-mismatch: {:d} versus {:d}".format(len(t), len(wt))
plt.plot(t, wt, label='w0')
A = 2
tao = 1
t = np.linspace(1, 2, 101)
wt = A * (np.exp(-t / tao) - 1 + 1 / tao)
assert len(t) == len(wt),\
    "Length-mismatch: {:d} versus {:d}".format(len(t), len(wt))
plt.plot(t, wt, label='w1')
A = 0.08
tao = -10
t = np.linspace(0, 10, 101)
wt = A * (np.exp(-t / tao) - 1 + 1 / tao)
assert len(t) == len(wt),\
    "Length-mismatch: {:d} versus {:d}".format(len(t), len(wt))
plt.plot(t, wt, label='w2')
A = -15
tao = 1
t = np.linspace(0, 10, 101)
wt = A * (np.exp(-t / tao) - 1 + 1 / tao)
assert len(t) == len(wt),\
    "Length-mismatch: {:d} versus {:d}".format(len(t), len(wt))
plt.plot(t, wt, label='w3')
"""plt.figure()
ax=plt.gca()"""
ax.set_title("novick", size=24, weight='bold')
ax.set_xlabel("Time [hours]")
ax.set_ylabel("Fraction of maximum beta-galactosidase activity")
wt_data = np.loadtxt(r'python物理建模初学者指南\4.2\g149novickA.txt', delimiter=',')
t = wt_data[:, 0]
wt = wt_data[:, 1]
assert len(t) == len(wt),\
    "Length-mismatch: {:d} versus {:d}".format(len(t), len(wt))
plt.plot(t, wt, label='wA')
wt_data = np.loadtxt(r'python物理建模初学者指南\4.2\g149novickB.txt', delimiter=',')
t = wt_data[:, 0]
wt = wt_data[:, 1]
assert len(t) == len(wt),\
    "Length-mismatch: {:d} versus {:d}".format(len(t), len(wt))
plt.plot(t, wt, label='wB')
plt.xlim(0, 10)
plt.legend()
plt.show()
