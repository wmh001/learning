# while循环简介

# 使用while循环
current_number = 1
while current_number <= 5:
    print(current_number)
    current_number += 1

# 让用户选择何时退出
prompt = "\nTell me something, and I will repeat it back to you:"
prompt += "\nEnter 'puit' to end the program. "
message = ""
while message != 'quit':
    message = input(prompt)
    if message != 'quit':
        print(message)

# 使用标志
actice = True
while actice:
    message = input(prompt)

    if message == 'quit':
        actice = False
    else:
        print(message)

# 使用break退出循环
prompt = "\nPlease enter the name of a city you have visited:"
prompt += "\n(Enter 'puit' when you are finished.) "
while True:
    city = input(prompt)

    if city == 'quit':
        break
    else:
        print("I'd love to go to " + city.title() + "!")

# 在循环中使用continue
