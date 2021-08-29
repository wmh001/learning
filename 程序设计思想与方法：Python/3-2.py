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
    x = int(input("Input a number: "))
    sum = sum + x
    moredata = input("More?(yes/no)")
print("The sum is" + " " + str(sum))
