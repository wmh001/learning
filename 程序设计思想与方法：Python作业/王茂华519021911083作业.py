'''# 作业一3.12
while True:
    try:
        # 以千克为单位输入体重
        weight = input("请输入体重（单位：千克）：")
        # 转换数据类型为浮点型
        Weight = float(weight)
    # 输入的字符不是数字，重新输入
    except ValueError:
        print("请输入数字！")
        continue
    # 输入的数字为正，跳出循环
    if Weight > 0:
        break
    # 输入的数字不是正数，重新输入
    else:
        print("请输入正数！")

while True:
    try:
        # 以米为单位输入身高
        height = input("请输入身高（单位：米）：")
        # 转换数据类型为浮点型
        Height = float(height)
    # 输入的字符不是数字，重新输入
    except ValueError:
        print("请输入数字！")
        continue
    # 输入的数字为正，跳出循环
    if Height > 0:
        break
    # 输入的数字不是正数，重新输入
    else:
        print("请输入正数！")

# 计算并输出BMI值（保留两位小数）
BMI = Weight / Height**2
print("BMI为%.2f" % (BMI))

# 判断健康信息
# BMI在19以下为轻体重
if BMI < 19:
    print("轻体重")
# BMI在[19, 25)之间为健康体重
elif BMI < 25:
    print("健康体重")
# BMI在[25,28)为超重
elif BMI < 28:
    print("超重")
# BMI在28以上为肥胖
else:
    print("肥胖")'''

# 作业二3.20
# 初始化变量
sum = 0
# 取1到1000中3的倍数依次循环
for i in range(0, 1001, 3):
    # 是否能被不能被5整除
    if (i % 5 != 0):
        # 求和
        sum += i
# 输出和
print("从1到1000的能被3整除且不能被5整除的所有整数之和为" + str(sum))

# 作业一3.12
# 初始化变量
Weight = 0
while Weight <= 0:
    try:
        # 以千克为单位输入体重
        weight = input("请输入体重（单位：千克）：")
        # 转换数据类型为浮点型
        Weight = float(weight)
        # 输入的数字不是正数，提醒并重新输入
        if Weight <= 0:
            print("请输入正数！")
    # 输入的字符不是数字，提醒并重新输入
    except ValueError:
        print("请输入数字！")

# 初始化变量
Height = 0
while Height <= 0:
    try:
        # 以米为单位输入身高
        height = input("请输入身高（单位：米）：")
        # 转换数据类型为浮点型
        Height = float(height)
        # 输入的数字不是正数，提醒并重新输入
        if Height <= 0:
            print("请输入正数！")
    # 输入的字符不是数字，提醒并重新输入
    except ValueError:
        print("请输入数字！")

# 计算并输出BMI值（保留两位小数）
BMI = Weight / Height**2
print("BMI为%.2f" % (BMI))

# 判断健康信息
# BMI在19以下为轻体重
if BMI < 19:
    print("轻体重")
# BMI在[19, 25)之间为健康体重
elif BMI < 25:
    print("健康体重")
# BMI在[25,28)为超重
elif BMI < 28:
    print("超重")
# BMI在28以上为肥胖
else:
    print("肥胖")
