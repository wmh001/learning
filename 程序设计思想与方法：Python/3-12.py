while True:
    try:
        weight = input("请输入体重（单位：千克）：")
        Weight = float(weight)
    except ValueError:
        print("请输入数字！")
        continue
    if Weight > 0:
        break
    else:
        print("请输入正数！")
while True:
    try:
        height = input("请输入身高（单位：米）：")
        Height = float(height)
    except ValueError:
        print("请输入数字！")
        continue
    if Height > 0:
        break
    else:
        print("请输入正数！")
BMI = Weight / Height**2
print("BMI为%.2f" % BMI)
if BMI < 19:
    print("轻体重")
elif BMI < 25:
    print("健康体重")
elif BMI < 28:
    print("超重")
else:
    print("肥胖")
