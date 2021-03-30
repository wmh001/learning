# 输入一个四位整数，对其加密后输出
# 加密方法：每位数字分别加9后除以10取余数，从而得到四位新数字。然后将千位和十位数字互换,百位和个位数字互换。

# 输入四位整数
num = input("请输入四位整数：")
# 将字符串转换为整数
Num = int(num)
# 取个位
digit3 = Num % 10
# 取十位
digit2 = (Num % 100 - digit3) / 10
# 取百位
digit1 = (Num % 1000 - digit2 * 10 - digit3) / 100
# 取千位
digit0 = (Num - digit1 * 100 - digit2 * 10 - digit3) / 1000
# 分别加密
digit0 = int((digit0 + 9) % 10)
digit1 = int((digit1 + 9) % 10)
digit2 = int((digit2 + 9) % 10)
digit3 = int((digit3 + 9) % 10)
# 输出结果
print("加密后的数字为：" + str(digit2) + str(digit3) + str(digit0) + str(digit1))
