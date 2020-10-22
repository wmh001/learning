# 使用字典

# 根据键的字典的访问
alien_0 = {'color': 'green'}
print(alien_0['color'])
alien_0 = {'color': 'green', 'points': 5}
new_points = alien_0['points']
print('You just earned ' + str(new_points) + ' points!')

# 添加键-值对
alien_0['x_position'] = 0
alien_0['y_position'] = 25
print(alien_0)
# 某些环境下，键-值对的排列顺序与添加顺序不同

# 先创建空字典
alien_0 = {}
print(alien_0)
alien_0['color'] = 'green'
alien_0['points'] = 5
print(alien_0)

# 修改字典中的值
alien_0 = {'color': 'green'}
print("The alien is " + alien_0['color'] + ".")
alien_0['color'] = 'yellow'
print("The alien is now " + alien_0['color'] + ".")

# 删除键-值对
alien_0 = {'color': 'green', 'points': 5}
print(alien_0)
del alien_0['points']
print(alien_0)

# 由类似对象组成的字典
favorite_languages = {
    'jen': 'python',
    'sarah': 'c',
    'edward': 'rudy',
    'phil': 'python',
}
print(
    "Sarah's favorite language is " +
    favorite_languages['sarah'].title() +
    ".")
