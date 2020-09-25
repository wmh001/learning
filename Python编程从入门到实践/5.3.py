# 简单的if语句
age = 19
if age >= 18:
    print("You are old enough to vote!")
    # 所有缩进的代码都属于程序块
    print("Have you registered to vote yet?")
# if-else语句
age = 17
if age >= 18:
    print("You are old enough to vote!")
    print("Have you registered to vote yet?")
else:
    print("Sorry, you are too young to vote.")
    print("Please regiater to vote as you as turn 18!")
# if-elif-else
age = 12
if age < 4:
    print("Your admission cost is $0.")
elif age < 18:
    print("Your admission cost is $5.")
else:
    print("Your admission cost is $10.")
# if-elif-elif
age = 12
if age < 4:
    print("Your admission cost is $0.")
elif age < 18:
    print("Your admission cost is $5.")
elif age < 65:
    print("Your admission cost is $10.")
elif age > 65:
    print("Your admission cost is $5.")
