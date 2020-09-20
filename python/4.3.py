# range(,)生成数字
# 生成1到4
for value in range(1, 5):
    print(value)
# list(range(,))创建列表
numbers = list(range(1, 6))
print(numbers)
# list(range(,,))生成等差数列
even_numbers = list(range(2, 11, 2))
print(even_numbers)
# 生成平方数列
squares = []
for value in range(1, 11):
    squares.append(value**2)
print(squares)
# min()求列表最小值
print(min(squares))
# max()求列表最大值
print(max(squares))
# sum()求列表总和
print(sum(squares))
# 列表解析,for循环与创建新元素合并为一行
# 列表名 = [目标值 for 直接生成值 in range()]
squares = [value**2 for value in range(1, 10)]
print(squares)
