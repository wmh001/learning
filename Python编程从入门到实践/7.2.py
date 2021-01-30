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
