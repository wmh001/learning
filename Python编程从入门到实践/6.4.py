# 嵌套

# 字典列表
alien_0 = {'color': 'green', 'point': 5}
alien_1 = {'color': 'yellow', 'point': 10}
alien_2 = {'color': 'red', 'point': 15}

aliens = [alien_0, alien_1, alien_2]

for alien in aliens:
    print(alien)

aliens = []
for alien_number in range(30):
    new_alien = {'color': 'green', 'point': 5, 'speed': 'slow'}
    aliens.append(new_alien)
for alien in aliens[:5]:
    print(alien)
print("...")
print("Total number of aliens: " + str(len(aliens)))

for alien in aliens[0:3]:
    if alien['color'] == 'green':
        alien['color'] = 'yellow'
        alien['speed'] = 'medium'
        alien['point'] = 10
for alien in aliens[:5]:
    print(alien)
print("...")

# 列表字典
pizza = {'crust': 'thick', 'toppings': ['mushrooms', 'extra pizza']}
print("You order a " + pizza['crust'] + "-crust pizza " + "with the following toppings:")
for topping in pizza['toppings']:
    print("\t" + topping)
