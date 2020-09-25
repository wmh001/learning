# .sort()永久字典排序
cars = ['bmw', 'audi', 'toyota', 'subaru']
cars.sort()
print(cars)
# .sort(reverse=True)永久逆向排序
cars.sort(reverse=True)
print(cars)
# sort()临时排序
print(sorted(cars))
print(cars)
# sorted(reverse=True)临时逆向排序
cars.sort()
print(sorted(cars, reverse=True))
print(cars)
# .reverse()反转顺序
c = cars[2]
cars[2] = cars[3]
cars[3] = c
print(cars)
cars.reverse()
print(cars)
# len计算列表元素数
print(len(cars))
