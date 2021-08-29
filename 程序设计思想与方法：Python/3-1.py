# -*-coding:utf-8-*-
# 数据处理的流程控制：分支控制
import math

# 单分支结构
"""
if <条件>:
    <语句体>
"""
# 计算<条件>的真假。若为真，则执行<语句体>，并把控制转向下一条语句；若为假，则直接把控制转向下一条语句。
# <条件>是一个布尔表达式

# 简单布尔表达式：<表达式1> <关系运算符> <表达式2>
# 关系运算: <、<=、==、>=、>、!=
# 数值比较、字符串比较（按字典序，字符序由编码(ASCII等)决定）、列表、元组的比较

# 复杂布尔表达式：<布尔表达式1><布尔运算><布尔表达式2>
# 布尔运算：and、or、not
# <布尔表达式1> and <布尔表达式2>、<布尔表达式1> or <布尔表达式2>、not <布尔表达式>
# 优先级：not最高, and次之, or最低

# 温度转换程序，增加热浪告警功能
f = float(input("华氏度："))
c = (f - 32) * 5.0 / 9
print("摄氏度：" + str(c))
if c > 35:
    print("警告：高温!")

# 两路分支结构
"""
if <条件>:
    <if-语句体>
else:
    <else-语句体>
"""
# if和else是非此即彼的关系
# 以下程序逻辑有误
if c >= 35:
    print("警告：高温!")
else:
    print("警告：低温!")

# 多路分支结构

# if语句嵌套
# 缺点：可读性差、代码松散
if c >= 35:
    print("警告：高温!")
else:
    if c <= -6:
        print("警告：低温!")
    else:
        print("舒适!")

# if-elif-else结构
if c >= 35:
    print("警告：高温!")
elif c <= -6:
    print("警告：低温!")
else:
    print("舒适!")

# 错误检测代码
# 利用if判断是否发生了某种运行错误
# 缺点：解决问题的算法被分割
a = float(input("输入a: "))
b = float(input("输入b: "))
c = float(input("输入c: "))
discrim = b * b - 4 * a * c
if discrim >= 0:
    discRoot = math.sqrt(discrim)
    root1 = (-b + discRoot) / (2 * a)
    root2 = (-b - discRoot) / (2 * a)
    print("解是:" + str(root1) + ' ' + str(root2))
else:
    print("方程无解!")

# 异常处理机制
# 缺省异常处理：程序运行出错时，抛出错误种类、位置等基本信息
"""
>>>a = "Hello"
>>>print(a[5])
Traceback (most recent call last): File "<stdin>",line 1,in <module>
IndexError:string index out of range
"""
"""
if doStep1() == ERROR1:
    处理代码1
elif doStep2() == ERROR2:
    处理代码2
elif doStep3() == ERROR3:
    处理代码3
"""

# 自定义异常处理：try-except语句
"""
>>>a = "Hello"
>>>try:
    print(a[5])
except IndexError:
    print("Index wrong!")

Index wrong!
"""
"""
try:
    doStep1()
    doStep2()
    doStep3()
except ERROR1:
    处理代码1
except ERROR2:
    处理代码2
except ERROR3:
    处理代码3
"""
# 优点：保持核心算法的清晰
try:
    a = float(input("输入a: "))
    b = float(input("输入b: "))
    c = float(input("输入c: "))
    discRoot = math.sqrt(discrim)
    root1 = (-b + discRoot) / (2 * a)
    root2 = (-b - discRoot) / (2 * a)
    print("解是:" + str(root1) + ' ' + str(root2))
except ValueError:
    print("方程无解!")
