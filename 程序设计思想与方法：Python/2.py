# 数据
# 现实世界事实或信息在计算机中的符号化表示
import sys

# 计算=数据+处理
# 计算机=数据处理机器
# 问题求解=信息的表示+处理的表示
# 程序=数据+流程控制

# 字面值：从表面形式就知道是什么数据

# 标识符：用名字表示数据
# 通过赋值语句定义变量
PI = 3.14159265
s = "Hello, World!"
print(s)
s = 3.14
print(s)

# 数据类型
# 不同数据类型具有不同的存储方式和处理方式

# 整数类型int
# 合法值：整数。默认十进制，0b开头二进制，0o开头八进制，0x开头十六进制
# 合法运算：加+、减/求负-、乘*、除/、乘方**、余数%
# Python2.x 10/3=3   Python3.x 10/3=3.333... 10//3=3

# Python3.x
# int理论上无限大，但大整数处理速度慢

# Python2.x
# int范围为-2**31~2**31-1
# long范围理论上为无限大，但运算效率远低于int。合法值有5L、2l、1234567890000L（打印出无l/L）
# 自动类型转换：long->int
# 2**31-1=2147483647L 2**30-1+2**30=2147463647

# 浮点数类型float
# 合法值：小数（3.14、-2.718、13.、0.0）。
# 合法运算：加+、减-、乘*、除/、乘方**、余数%
# 计算机只能存储浮点数的近似值
print(1.2 - 1.0)
print(2.2 - 1.2)
print(2.0 - 1.0)
print(abs(1.0000000000000001 - 1))
# 系统可区分的浮点数最小差为
print(sys.float_info.epsilon)
# 对于很大和很小的浮点数，Python自动用科学计数法
# 自动类型转换：int->long->float、int->float

# 人工类型转换：float(参数)、int(参数)
print(float(1))
print(int(1.5))

# 自动转换：int、long、float；int、float
# python2中，avg = sum / count将取整，avg = float(sum) / count将获得实际值
# python2中，avg = sum / count将获得实际值，avg = int(sum / count)将取整

# 数学模块
# 模块：包含许多有用的定义，也称为库。最常见的是函数定义，也有类定义。一般由系统提供，也可自己开发
# math模块：包含有用的数学函数定义
# import语句：将别人的模块定义导入我的模块

# 库的两种导入方式：
# import math           #给你一包糖果
# from math import *    #从包中取出糖果给你

# 导入后对库函数的调用：例如求平方根
# math.sqrt(4)          #要说包里的某颗糖果
# sqrt(4)               #直接说某颗糖果

# 数学库中的常用函数
# pi：常数π
# e：常数e
# sqrt(x)：平方根
# sin(x)，cos(x)，tan(x)，asin(x)，acos(x)，atan(x)：三角函数和反三角函数
# log(x)，log10(x)：自然对数与常用对数
# exp(x)：e的x次方
# ceil(x)：≥x的最小整数
# floor(x)：≤x的最大整数
# degrees(r)：r弧度转换为度
# hypot(x,y)：返回根号(x^2+y^2)
