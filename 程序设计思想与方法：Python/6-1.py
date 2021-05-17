# -*-coding:utf-8-*-
# 大量数据的表示和处理

# 序列
# 包括str,list,tuple

# 通用的序列操作
# s1 + s2 返回拼接后序列
# n * s1 或s1 * n 返回拼接n个相同序列后的序列
# s[i], s[i:j], s[i:j:k] 返回第i个元素，返回第i到第j-1个元素组成的序列，返回第i到第j-1个元素且步长为k的元素组成的序列
# len(s) 返回序列中元素的个数
# max(s) 返回序列中按字典排序方法值最大的元素
# min(s) 返回序列中按字典排序方法值最小的元素
# x in s 或 x not in s 判断元素x是否为s中的元素

# 字符串
# 元素不能修改
s = "I think, therefore I am."
# 字符串.count(字符)，返回个数，统计字符串中的某字符个数
print(s.count('I'))
# 字符串.find('字符串')，返回序数，寻找子字符串在字符串中的位置
print(s.find('re'))
# 字符串.lower()，返回新字符串，所有字母小写
print(s.lower())
# 字符串.replace('字符1', '字符2')，返回新字符串，将原字符串中的字符1换为字符2
print(s.lower().replace('i', 'I'))
# 字符串.split('字符')，返回拆分所得字符串列表，将字符串以字符为分隔拆分为字符串列表，默认参数为' '
print(s.split())
