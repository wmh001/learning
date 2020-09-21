# 检查是否相等
print('bwm' == 'bwm')
print('audi' == 'bmw')
# 检查大小写是否相同
print('Audi' == 'audi')
print('Audi'.lower() == 'audi')
# 检查是否不相等
print('mushroom' != 'anchovies')
# 比较数字
print(18 == 18)
print(17 != 42)
print(19 < 21)
print(19 <= 21)
print(19 > 21)
print(19 >= 21)
# 检查多个条件
# 且
print(22 >= 21 and 18 >= 21)
print(22 >= 21 and 22 >= 21)
# 或
print(21 >= 22 or 18 >= 22)
print(18 >= 22 or 18 >= 22)
# 检查特定值是否在列表中
requested_toopings = ['mushrooms', 'onions', 'pineapple']
print('mushrooms' in requested_toopings)
print('pepperoni' in requested_toopings)
# 检查特定值是否不在列表中
banned_users = ['andrew', 'carolina', 'david']
print('marie' not in banned_users)
