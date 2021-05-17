# 序列
# 包括str,list,tuple

# 通用的序列操作
# s1 + s2 序列相拼接
# n * s1 或s1 * n
# s[i],s[i:j],s[i:j:k]
# len(s)
# max(s)
# min(s)
# x in s 或 x not in s

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
