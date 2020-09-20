# 元组
# 元组的值不能修改
dimensions = (200, 50)
print(dimensions[0])
print(dimensions[1])
# dimensions[0] = 250
# 遍历元组
for dimension in dimensions:
    print(dimension)
# 元组可以修改
dimensions = (400, 100)
for dimension in dimensions:
    print(dimension)
