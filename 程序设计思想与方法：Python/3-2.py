# -*-coding:utf-8-*-
# 数据处理的流程控制：循环控制

# for循环
# 主要用于确定次数的循环
"""
for <循环控制变量> in <序列>:
    <循环体>
"""
# 序列可以仅为计数器，也可以为循环体处理的数据
for i in [1, 2, 3, 4, 5]:
    print(i)

data = ['Born on:', 'July', 2, 2005]
# 直接遍历序列
for d in data:
    print(d)
# 通过索引遍历序列
for i in range(len(data)):
    print(data[i])
for i in range(0, len(data), 3):
    print(data[i])

# 处理字符串
for c in "hello world":
    print(c)
# 处理元组
for i in (1, 2, 3):
    print(i)
# 处理嵌套序列
for t in [(1, 2), (3, 4), (5, 6)]:
    print(t,  t[0], t[1])

# while循环
# 主要用于不确定次数的循环
"""
while <布尔表达式>:
    <循环体>
"""
# 循环前测试条件，若不满足,则循环体一次都不执行
# 循环体必须影响下一次条件测试，否则导致无穷循环
i = 0
while i < 10:
    print(i)
    i = i + 1

# 交互循环：根据用户交互来决定是否循环下去
sum = 0
moredata = "yes"
while moredata[0] == "y":
    x = int(input("输入一个数: "))
    sum = sum + x
    moredata = input("继续输入吗?(yes/no)")
print("和是" + " " + str(sum))

# 哨兵循环：设置一个特殊数据值(称为哨兵)作为终止循环的信号
"""
前导输入
while 该数据不是哨兵:
    处理该数据
    循环尾输入(下一个数据)
"""
# 正常数据是非负数，则可以-1作为哨兵
sum = 0
x = int(input("输入一个数(输入-1结束)： "))
while x >= 0:
    sum = sum + x
    x = int(input("输入一个数(输入-1结束)： "))
print("和是" + " " + str(sum))
# 正常数据是任何实数,则可以空串作为哨兵
sum = 0
x = input("输入一个数(回车结束)： ")
while x != "":
    sum = sum + eval(x)
    x = input("输入一个数(回车结束)： ")
print("和是" + " " + str(sum))

# 后测试循环：执行循环体后才测试条件，循环体至少执行一次，直至条件成立才退出循环
# Python可用while实现，只需确保首次进入while时条件成立
"""
x = -1
while x < 0: ...
"""

# while计数器循环
"""
计数器count置为0
while count < n:
    处理代码
    count ＝ count + 1
"""
i = 0
while i < 10:
    print(i)
    i = i + 1
i = 10
while i > 0:
    print(i)
    i = i - 1

# 循环非正常中断:break
# 输入合法性检查
while True:
    x = eval(input("请输入非负数:"))
    if x >= 0:
        break
# break也可以跳出for循环
for i in range(10):
    print("烦")
    if i > 4:
        break
# 慎用break!尤其是一个循环体中有多个break

# 循环非正常中断:continue
# 中止本轮循环,控制转移到所处循环语句的开头“继续”下一轮循环
# 对列表中的奇数求和
a = [23, 28, 39, 44, 50, 67, 99]
sum = 0
for i in a:
    if i % 2 == 0:
        continue
    sum = sum + i
print(sum)

# 嵌套循环：一个循环的循环体中有另一个循环
# 打印乘法口诀表
for i in range(1, 10):
    for j in range(1, i + 1):
        print("%dx%d=%-3d" % (j, i, j*i), end="")
    print()

# 程序设计的发展：
#     早期:手工作坊式，程序规模小、功能简单，要在有限内存中尽快完成计算，凭借程序员的个人编程技巧
#     后来:作为工程来开发，程序规模大、功能复杂，内存和速度不是问题，软件正确性和开发效率变得突出，依靠系统化的开发方法和工具
# 程序开发周期：
#     明确需求:问题是什么?用户要求是什么?
#     制定程序规格:描述“做什么”
#     设计程序逻辑:描述“怎么做”
#     实现:用编程语言编写代码
#     测试与排错:用样本数据执行程序，测试结果是否与预期吻合，有错则排错
#     维护:根据用户需求持续改进程序
# 什么是好的程序：
#     解决同一个问题，可以设计出多种处理过程，即编制多种程序
#     即使各种程序都正确，仍然有好坏之分
#     除了正确性，好的程序应该是：效率高、易理解、易维护、可扩展
# 如何得到好的程序：
#     手工作坊阶段靠的是个人编程技巧
#     如今则依靠程序设计方法和工具
#         方法:结构化方法,模块化方法,面向对象方法等
#         工具:建模工具,集成开发环境,项目管理工具等

# 结构化程序设计一：确保程序具有良好的文本结构，使程序易理解、易验证、易维护
# 基本原则：只使用顺序，分支，循环三种基本控制结构；goto有害，好在goto不是必须的；break和continue有点类似goto,因此要慎用

# 结构化程序设计二：单入口单出口的程序块
# 多条语句可以组合成程序块,只要是单入口单出口,仍然可当作一条语句

# 编程案例：求最大值
x1 = 1
x2 = 2
x3 = 3
# 策略1:每个数都与其他数比较大小
if x1 >= x2 and x1 >= x3:
    m = x1
elif x2 >= x1 and x2 >= x3:
    m = x2
else:
    m = x3
print(m)
# 此算法中各分支彼此独立，但实际上一个分支的信息对其他分支是有用的。此算法仅适合3个数的情况

# 策略2:判定树
if x1 >= x2:
    if x1 >= x3:
        m = x1
    else:
        m = x3
else:
    if x2 >= x3:
        m = x2
    else:
        m = x3
print(m)
# 好处：只需两次比较,效率高
# 坏处：结构复杂, 复杂度随n爆炸式增长

# 策略3：顺序处理，记录当前最大值
m = x1
if x2 >= m:
    m = x2
if x3 >= m:
    m = x3
# 效率高、易读易理解、可扩展到n个
n = eval(input("几个数? "))
m = eval(input("输入一个数："))
for i in range(n-1):
    x = eval(input("输入一个数："))
    if x > m:
        m = x
print(m)

# 策略4:利用现成代码.
# Python提供内建函数max(x1, x2, ... , xn)
print(max(x1, x2, x3))
