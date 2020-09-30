# -*- coding: utf-8 -*-
"""
Created on Tue Sep 29 23:27:27 2020

@author: w'm'h (python3.8)
"""
import numpy as np
# 分支
for trial in range(5):
    # input("") 显示字符串并等待输入，enter结束
    userInput = input('Pick a number: ')
    number = float(userInput)
    # if语句
    """if 逻辑表达式:
           程序块1
       else:
           程序块2
    逻辑表达式为True，执行程序块1，否则执行程序块2"""
    if number < 0:
        print('Square rook is not real')
    else:
        print('Square root of {} is {:.4f}'.format(number, np.sqrt(number)))
    userAgain = input('Another [y/n]?')
    # !=不等于
    # 逻辑表达式可以用not求反
    # if userAgain != 'y':
    if not (userAgain == 'y'):
        # break语句退出循环
        break
# %%
"""if 逻辑表达式1:
       程序块1
   elif 逻辑表达式2:
       程序块2
   else:
       程序块3"""
if trial == 4:
    print('Srry, only 5 per customer.')
elif userAgain == 'n':
    print('Bye!')
else:
    print('Sorry, I did not understand that.')
# 关系操作符：<,>,==,<=,>=,!=
# 布尔操作符：and,or,end
# True:任何非零数值、非空列表、非空字符串、非空元组、非空数组
# False:False、None、[]、()、{}、0、0.0、0j

# %%
