# 列表切片
# 取0到2
players = ['charles', 'martina', 'michael', 'florence', 'eli']
print(players[0:3])
# 取1到3
print(players[1:4])
# 第一个索引省略时，默认为0
print(players[:4])
# 第二个索引省略时，默认为最后一个元素
print(players[2:])
print(players[-3:])
# 遍历切片
print("Here are the first three players on my team: ")
for player in players[:3]:
    print(player.title())
# 复制列表
my_food = ['pizza', 'falafel', 'carrot cake']
friend_food = my_food[:]
print(my_food)
print(friend_food)
my_food.append('cannoli')
friend_food.append('ice cream')
print(my_food)
print(friend_food)
# 给列表起别名
friend_food = my_food
print(friend_food)
my_food.append('ice cream')
print(friend_food)
