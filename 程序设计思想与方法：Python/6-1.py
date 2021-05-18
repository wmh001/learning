# -*-coding:utf-8-*-
# 数据复杂性
# 数据量
# 数据关系

# 大量数据的表示和处理
# 数据集合体

# 序列
# 包括str,list,tuple

# 通用的序列操作
# s1 + s2 返回联接后序列
# n * s1 或s1 * n 返回n个相同序列联接后的序列
# s[i], s[i:j], s[i:j:k] 返回第i个元素，返回第i到第j-1个元素组成的序列，返回第i到第j-1个元素且步长为k的元素组成的序列
# len(s) 返回序列中元素的个数
# max(s) 返回序列中按字典排序方法值最大的元素
# min(s) 返回序列中按字典排序方法值最小的元素
# x in s 或 x not in s 判断元素x是否为s中的元素

# 字符串
# 元素不能修改
# 元素为字符类型
s = "I think, therefore I am."
# 字符串.capitalize()首字母大写，不改变原字符串，返回新字符串
print(s.capitalize())
print(s)
print()
# 字符串.center(宽度)扩展字符串到给定宽度且字符串居中，不改变原字符串，返回新字符串
print(s.center(30) + '|')
print(s)
# 字符串.count(字符)统计字符串中的某字符个数，返回个数
print(s.count('I'))
# 字符串.find(字符串)寻找子字符串在字符串中的首次出现的位置，返回索引
print(s.find('re'))
# 字符串.ljust(宽度)扩展字符串到给定宽度且字符串居左，不改变原字符串，返回新字符串
print(s.ljust(30) + '|')
print(s)
print()
# 字符串.lower()所有字母小写，不改变原字符串，返回新字符串
print(s.lower())
print(s)
print()
# 字符串.lstrip()删除字符串前导空格，不改变原字符串，返回新字符串
s0 = '   ' + s + '   '
print(s0.lstrip() + '|')
print(s0 + '|')
print()
# 字符串.replace(字符1, 字符2)原字符串中的字符1换为字符2，不改变原字符串，返回新字符串
print(s.replace('t', 'T'))
print(s)
# 字符串.rfind(字符串)寻找子字符串在字符串中的最后一次出现的位置，返回索引
print(s.rfind('re'))
# 字符串.rjust(宽度)扩展字符串到给定宽度且字符串居右，不改变原字符串，返回新字符串
print(s.rjust(30) + '|')
print(s)
print()
# 字符串.rstrip()删除字符串尾部空格，不改变原字符串，返回新字符串
s0 = '   ' + s + '   '
print(s0.rstrip() + '|')
print(s0 + '|')
# 字符串.split(字符)，返回拆分所得字符串列表，将字符串以字符为分隔拆分为字符串列表，默认参数为' '
print(s.split())
# 字符串.upper()所有字母大写，不改变原字符串，返回新字符串
print(s.upper())
print(s)

# 列表
# 元素可以修改
# 每个元素都可以为任意类型
# del s[i]
# del s[i:j]删除所选元素
a = ['Irrational', [3.14, 2.718], 'pi and e']
del a[1:2]
print(a)
del a[0]
print(a)
