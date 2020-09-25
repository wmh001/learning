# 修改列表
# 修改列表元素
motorcycles = ['honda', 'yamaha', 'suzuki']
print(motorcycles)
motorcycles[0] = 'ducati'
print(motorcycles)
# .append()在列表尾添加元素
motorcycles.append('honda')
print(motorcycles)
motorcycles = []
print(motorcycles)
motorcycles.append('honda')
motorcycles.append('yamaha')
motorcycles.append('suzuki')
print(motorcycles)
# .insert(,)在索引处插入元素
motorcycles.insert(1, "ducati")
print(motorcycles)
# del语句删除元素
del motorcycles[1]
print(motorcycles)
# .pop()删除并返回最后一个元素（弹出）
print(motorcycles.pop())
print(motorcycles)
# .pop()弹出任何位置的元素
print(motorcycles.pop(1))
print(motorcycles.pop(0))
print(motorcycles)
# .remove()根据值删除元素
motorcycles.append('honda')
motorcycles.append('yamaha')
motorcycles.append('suzuki')
motorcycles.append("ducati")
print(motorcycles)
motorcycles.remove('ducati')
print(motorcycles)
m = 'yamaha'
motorcycles.remove(m)
print(motorcycles)
